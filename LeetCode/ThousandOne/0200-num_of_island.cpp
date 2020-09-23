#include "leetcode.hpp"

/* 200. 岛屿数量

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

示例 1:
输入:
11110
11010
11000
00000
输出: 1

示例 2:
输入:
11000
11000
00100
00011
输出: 3
解释: 每座岛屿只能由水平和/或竖直方向上相邻的陆地连接而成。
*/

int numIslands(vector<vector<char>>& grid)
{
	int const dir[] = { -1, 0, 1, 0, -1 };
	if (grid.empty())
		return 0;
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	int count = 0;
	vector<pair<int, int>> current, nextloop;
	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
			if (grid[h][w] == '1')
			{
				++count;
				grid[h][w] = '2';
				current.push_back({ h, w });
				while (!current.empty())
				{
					nextloop.clear();
					for (pair<int, int> cur : current)
						for (int d = 0; d < 4; ++d)
						{
							int y = cur.first + dir[d];
							int x = cur.second + dir[d + 1];
							if (static_cast<unsigned>(y) < static_cast<unsigned>(rows)
								&& static_cast<unsigned>(x) < static_cast<unsigned>(cols)
								&& grid[y][x] == '1')
							{
								grid[y][x] = '2';
								nextloop.push_back({ y, x });
							}
						}
					nextloop.swap(current);
				}
			}
	return count;
}


int main()
{}
