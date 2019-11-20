#include "leetcode.hpp"

/* 695. 岛屿的最大面积

给定一个包含了一些 0 和 1的非空二维数组 grid , 一个岛屿是由四个方向 (水平或垂直) 的 1 (代表土地) 构成的组合。
你可以假设二维矩阵的四个边缘都被水包围着。
找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为0。)

示例 1:

[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]

对于上面这个给定矩阵应返回 6。注意答案不应该是11，因为岛屿只能包含水平或垂直的四个方向的‘1’。

示例 2:

[[0,0,0,0,0,0,0,0]]

对于上面这个给定的矩阵, 返回 0。

注意: 给定的矩阵grid的长度和宽度都不超过 50。
*/


int maxAreaOfIsland(vector<vector<int>>& grid)
{
	int const dir[5] = { -1, 0, 1, 0, -1 };
	unsigned rows = static_cast<unsigned>(grid.size());
	if (rows == 0)
		return 0;
	unsigned cols = static_cast<unsigned>(grid[0].size());
	size_t maxarea = 0;
	typedef pair<unsigned, unsigned> point;
	vector<point> visit;
	visit.reserve(rows * cols);
	for (unsigned h = 0; h < rows; ++h)
		for (unsigned w = 0; w < cols; ++w)
			if (grid[h][w])
			{
				visit.clear();
				visit.emplace_back(h, w);
				grid[h][w] = 0;
				for (size_t idx = 0; idx < visit.size(); ++idx)
				{
					point pt = visit[idx];
					for (int d = 0; d < 4; ++d)
					{
						unsigned y = pt.first + dir[d];
						unsigned x = pt.second + dir[d + 1];
						if (y < rows && x < cols && grid[y][x])
						{
							visit.emplace_back(y, x);
							grid[y][x] = 0;
						}
					}
				}
				maxarea = std::max(maxarea, visit.size());
			}
	return static_cast<int>(maxarea);
}


int main()
{
	vector<vector<int>> grid = {
		{ 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 },
		{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 }
	};
	OutExpr(maxAreaOfIsland(grid), "%d");
}
