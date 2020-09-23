#include "leetcode.hpp"

/* 1277. 统计全为 1 的正方形子矩阵

给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1。
请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。

示例 1：
输入：matrix =
[
	[0,1,1,1],
	[1,1,1,1],
	[0,1,1,1]
]
输出：15
解释：
边长为 1 的正方形有 10 个。
边长为 2 的正方形有 4 个。
边长为 3 的正方形有 1 个。
正方形的总数 = 10 + 4 + 1 = 15.

示例 2：
输入：matrix =
[
	[1,0,1],
	[1,1,0],
	[1,1,0]
]
输出：7
解释：
边长为 1 的正方形有 6 个。
边长为 2 的正方形有 1 个。
正方形的总数 = 6 + 1 = 7.

提示：
	1 <= arr.length <= 300
	1 <= arr[0].length <= 300
	0 <= arr[i][j] <= 1
*/

class Solution
{
public:
	int countSquares(vector<vector<int>>& M)
	{
		int sum = 0;
		int rows = static_cast<int>(M.size());
		int cols = static_cast<int>(M[0].size());
		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
				if (M[h][w])
				{
					int a = h > 0 ? M[h - 1][w] : 0;
					int b = w > 0 ? M[h][w - 1] : 0;
					int c = (h > 0 && w > 0) ? M[h - 1][w - 1] : 0;
					int d = 1 + min(min(a, b), c);
					M[h][w] = d;
					sum += d;
				}
		return sum;
	}
};


int main()
{
	vector<vector<int>>
		a = {
			{ 0, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 0, 1, 1, 1 },
	},
	b = {
		{ 1, 0, 1 },
		{ 1, 1, 0 },
		{ 1, 1, 0 },
	};
	Solution s;
	OutExpr(s.countSquares(a), "%d");
	OutExpr(s.countSquares(b), "%d");
}
