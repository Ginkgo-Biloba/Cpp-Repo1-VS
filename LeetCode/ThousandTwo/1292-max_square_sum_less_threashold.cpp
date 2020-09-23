#include "leetcode.hpp"

/* 1292. 元素和小于等于阈值的正方形的最大边长

给你一个大小为 m x n 的矩阵 mat 和一个整数阈值 threshold。

请你返回元素总和小于或等于阈值的正方形区域的最大边长；如果没有这样的正方形区域，则返回 0。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/12/15/e1.png
输入：mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
输出：2
解释：总和小于 4 的正方形的最大边长为 2，如图所示。

示例 2：
输入：mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
输出：0

示例 3：
输入：mat = [[1,1,1,1],[1,0,0,0],[1,0,0,0],[1,0,0,0]], threshold = 6
输出：3

示例 4：
输入：mat = [[18,70],[61,1],[25,85],[14,40],[11,96],[97,96],[63,45]], threshold = 40184
输出：2

提示：
	1 <= m, n <= 300
	m == mat.length
	n == mat[i].length
	0 <= mat[i][j] <= 10000
	0 <= threshold <= 10^5
*/

// https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/discuss/451909/C%2B%2B-Two-O(MN)-Solutions.-PrefixSum-%2B-SlidingWindow-or-PrefixSum-%2B-Smart-Enumeration
// 抄的
class Solution
{
	int rows, cols;
	vector<vector<int>> integral;

	int sqsum(int y2, int x2, int y1, int x1)
	{
		return integral[y2][x2]
			- integral[y2][x1]
			- integral[y1][x2]
			+ integral[y1][x1];
	}

public:
	int maxSideLength(vector<vector<int>>& mat, int threshold)
	{
		rows = static_cast<int>(mat.size());
		cols = static_cast<int>(mat[0].size());
		integral.resize(rows + 1);
		integral[0].assign(cols + 1, 0);
		for (int h = 1; h <= rows; ++h)
		{
			integral[h].resize(cols + 1);
			for (int w = 1; w <= cols; ++w)
				integral[h][w] = mat[h - 1][w - 1]
				+ integral[h][w - 1] + integral[h - 1][w] - integral[h - 1][w - 1];
		}

		int ans = 0;
		for (int h = 0; h <= rows; ++h)
			for (int w = 0; w < cols; ++w)
			{
				int len = ans + 1;
				while ((h + len <= rows)
					&& (w + len <= cols)
					&& (sqsum(h + len, w + len, h, w) <= threshold))
				{
					ans = len;
					++len;
				}
			}
		return ans;
	}
};


int main()
{
	vector<vector<int>>
		a = {
			{ 1, 1, 3, 2, 4, 3, 2 },
			{ 1, 1, 3, 2, 4, 3, 2 },
			{ 1, 1, 3, 2, 4, 3, 2 },
	},
	b = {
		{ 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2 },
	},
	c = {
		{ 1, 1, 1, 1 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
	},
	d = {
		{ 18, 70 },
		{ 61, 1 },
		{ 25, 85 },
		{ 14, 40 },
		{ 11, 96 },
		{ 97, 96 },
		{ 63, 45 },
	};
	Solution s;
	OutExpr(s.maxSideLength(a, 4), "%d");
	OutExpr(s.maxSideLength(b, 1), "%d");
	OutExpr(s.maxSideLength(c, 6), "%d");
	OutExpr(s.maxSideLength(d, 40184), "%d");
}
