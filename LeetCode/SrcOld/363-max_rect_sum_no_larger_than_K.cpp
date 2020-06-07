#include "leetcode.hpp"

/* 363. 矩形区域不超过 K 的最大数值和

给定一个非空二维矩阵 matrix 和一个整数 k，找到这个矩阵内部不大于 k 的最大矩形和。

示例:

输入: matrix = [[1,0,1],[0,-2,3]], k = 2
输出: 2
解释: 矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）。

说明：
	矩阵内的矩形区域面积必须大于 0。
	如果行数远大于列数，你将如何解答呢？
*/

// https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/discuss/83599/Accepted-C%2B%2B-codes-with-explanation-and-references
// 抄的
int maxSumSubmatrix(vector<vector<int>>& m, int k)
{
	int rows = static_cast<int>(m.size());
	int cols = static_cast<int>(m[0].size());
	int ans = INT_MIN;
	for (int w = 0; w < cols; ++w)
	{
		vector<int> sum(rows);
		for (int x = w; x < cols; ++x)
		{
			for (int y = 0; y < rows; ++y)
				sum[y] += m[y][x];

			set<int> acc;
			acc.insert(0);
			int cursum = 0, curmax = INT_MIN;
			for (int y = 0; y < rows; ++y)
			{
				cursum += sum[y];
				auto it = acc.lower_bound(cursum - k);
				if (it != acc.end())
					curmax = max(curmax, cursum - *it);
				acc.insert(cursum);
			}
			ans = max(ans, curmax);
		}
	}
	return ans;
}


int main()
{
	vector<vector<int>>
		a = {
			{ 1, 0, 1 },
			{ 0, -2, 3 },
	};
	OutExpr(maxSumSubmatrix(a, 2), "%d");
}
