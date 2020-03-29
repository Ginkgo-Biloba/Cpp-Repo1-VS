#include "leetcode.hpp"

/* 1139. 最大的以 1 为边界的正方形

给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大 正方形 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。

示例 1：
输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
输出：9

示例 2：
输入：grid = [[1,1,0,0]]
输出：1

提示：
	1 <= grid.length <= 100
	1 <= grid[0].length <= 100
	grid[i][j] 为 0 或 1
*/

// https://leetcode.com/problems/largest-1-bordered-square/discuss/345233/JavaC%2B%2BPython-Straight-Forward
// 抄的
class Solution
{
public:
	int largest1BorderedSquare(vector<vector<int>>& grid)
	{
		int rows = static_cast<int>(grid.size());
		int cols = static_cast<int>(grid[0].size());
		vector<vector<int>> lef = grid, top = grid;

		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
				if (grid[h][w])
				{
					if (w > 0)
						lef[h][w] += lef[h][w - 1];
					if (h > 0)
						top[h][w] += top[h - 1][w];
				}
				else
					lef[h][w] = top[h][w] = 0;

		for (int len = min(rows, cols); len > 0; --len)
			for (int h = 0; h <= rows - len; ++h)
				for (int w = 0; w <= cols - len; ++w)
				{
					if (min(
						min(top[h + len - 1][w], top[h + len - 1][w + len - 1]),
						min(lef[h][w + len - 1], lef[h + len - 1][w + len - 1]))
						>= len)
						return len * len;
				}
		return 0;
	}
};


int main()
{
	vector<vector<int>> grid = {
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
	};
	Solution s;
	OutExpr(s.largest1BorderedSquare(grid), "%d");
}
