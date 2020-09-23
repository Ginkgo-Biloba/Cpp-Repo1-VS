#include "leetcode.hpp"

/* 74. 搜索二维矩阵

编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。
该矩阵具有如下特性：
	每行中的整数从左到右按升序排列。
	每行的第一个整数大于前一行的最后一个整数。

示例 1:
输入:
matrix = [
	[1,   3,  5,  7],
	[10, 11, 16, 20],
	[23, 30, 34, 50]
]
target = 3
输出: true

示例 2:
输入:
matrix = [
	[1,   3,  5,  7],
	[10, 11, 16, 20],
	[23, 30, 34, 50]
]
target = 13
输出: false
*/

bool searchMatrix(vector<vector<int>>& M, int target)
{
	if (M.empty() || M[0].empty())
		return false;
	int rows = static_cast<int>(M.size());
	int cols = static_cast<int>(M[0].size());
	// 拉直
	int a = 0, b, c = rows * cols - 1;
	while (a < c)
	{
		b = (a + c) / 2;
		if (M[b / cols][b % cols] < target)
			a = b + 1;
		else
			c = b;
	}
	return M[a / cols][a % cols] == target;
}


int main()
{}
