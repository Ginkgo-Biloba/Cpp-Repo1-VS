#include "leetcode.hpp"

/* 73. 矩阵置零

给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。
请使用原地算法。

示例 1:
输入:
[
	[1,1,1],
	[1,0,1],
	[1,1,1]
]
输出:
[
	[1,0,1],
	[0,0,0],
	[1,0,1]
]

示例 2:
输入:
[
	[0,1,2,0],
	[3,4,5,2],
	[1,3,1,5]
]
输出:
[
	[0,0,0,0],
	[0,4,5,0],
	[0,3,1,0]
]

进阶:
	一个直接的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
	一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
	你能想出一个常数空间的解决方案吗？
*/

// https://leetcode.com/problems/set-matrix-zeroes/discuss/26014/Any-shorter-O(1)-space-solution
// 抄的
void setZeroes(vector<vector<int>>& M)
{
	if (M.empty())
		return;
	int rows = static_cast<int>(M.size());
	int cols = static_cast<int>(M[0].size());
	int col0 = 1;
	for (int h = 0; h < rows; ++h)
	{
		if (M[h][0] == 0)
			col0 = 0;
		for (int w = 1; w < cols; ++w)
			if (M[h][w] == 0)
				M[0][w] = M[h][0] = 0;
	}
	for (int h = rows - 1; h >= 0; --h)
	{
		for (int w = cols - 1; w >= 1; --w)
		{
			if (M[h][0] == 0 || M[0][w] == 0)
				M[h][w] = 0;
		}
		if (col0 == 0)
			M[h][0] = 0;
	}
}


int main()
{}
