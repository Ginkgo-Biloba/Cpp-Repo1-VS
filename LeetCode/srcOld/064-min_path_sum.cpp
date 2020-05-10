#include "leetcode.hpp"

/* 64. 最小路径和

给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

示例:
输入:
[
	[1,3,1],
	[1,5,1],
	[4,2,1]
]
输出: 7
解释: 因为路径 1→3→1→1→1 的总和最小。
*/

int minPathSum(vector<vector<int>>& grid)
{
	if (grid.empty())
		return 0;
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	for (int w = 1; w < cols; ++w)
		grid[0][w] += grid[0][w - 1];
	for (int h = 1; h < rows; ++h)
	{
		grid[h][0] += grid[h - 1][0];
		for (int w = 1; w < cols; ++w)
			grid[h][w] += min(grid[h - 1][w], grid[h][w - 1]);
	}
	return grid[rows - 1][cols - 1];
}


int main()
{}
