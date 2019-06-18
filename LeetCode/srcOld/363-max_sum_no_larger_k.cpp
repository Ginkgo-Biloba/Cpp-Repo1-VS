#include "../srcOld/utility.hpp"

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
int maxSumSubmatrix(vector<vector<int>>& matrix, int k)
{
	int rows = static_cast<int>(matrix.size());
	if (rows == 0) return 0;
	int cols = static_cast<int>(matrix[0].size());
	int ans = INT_MIN;
	vector<int> sum(rows);
	std::set<int> acc;

	for (int c = 0; c < cols; ++c)
	{
		memset(sum.data(), 0, rows * sizeof(int));
		for (int w = c; w < cols; ++w)
		{
			for (int r = 0; r < rows; ++r)
				sum[r] += matrix[r][w];

			acc.clear();
			acc.insert(0);
			int curSum = 0, curMax = INT_MIN;
			for (int s : sum)
			{
				curSum += s;
				auto it = acc.lower_bound(curSum - k);
				if (it != acc.end())
					curMax = std::max(curMax, curSum - *it);
				acc.insert(curSum);
			}
			ans = std::max(ans, curMax);
		}
	}

	return ans;
}


int main()
{
	vector<vector<int>> matrix = {
		{ 1, 0, 1 },
		{ 0, -2, 3 },
	};
	int ans = maxSumSubmatrix(matrix, 2);
	printf("maxSumSubmatrix: %d\n", ans);
}
