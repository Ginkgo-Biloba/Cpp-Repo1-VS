#include "leetcode.hpp"

/* 63. 不同路径 II

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。
机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。
那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。

说明：m 和 n 的值均不超过 100。

示例 1:

输入:
[
	[0,0,0],
	[0,1,0],
	[0,0,0]
]
输出: 2
解释:
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右
*/

int uniquePathsWithObstacles(vector<vector<int>>& grid)
{
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	grid[0][0] -= 1;
	for (int w = 1; w < cols; ++w)
	{
		if (grid[0][w] != 1)
			grid[0][w] = min(grid[0][w - 1], 0);
	}
	for (int h = 1; h < rows; ++h)
	{
		if (grid[h][0] != 1)
			grid[h][0] = min(grid[h - 1][0], 0);
		for (int w = 1; w < cols; ++w)
			if (grid[h][w] != 1)
			{
				grid[h][w] = 0U
					+ min(grid[h - 1][w], 0)
					+ min(grid[h][w - 1], 0);
			}
	}
	return max(-grid[rows - 1][cols - 1], 0);
}


int main()
{}
