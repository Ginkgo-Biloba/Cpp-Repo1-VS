#include "leetcode.hpp"

/* 1254. 统计封闭岛屿的数目

有一个二维矩阵 grid ，每个位置要么是陆地（记号为 0 ）要么是水域（记号为 1 ）。

我们从一块陆地出发，每次可以往上下左右 4 个方向相邻区域走，能走到的所有陆地区域，我们将其称为一座「岛屿」。

如果一座岛屿 完全 由水域包围，即陆地边缘上下左右所有相邻区域都是水域，那么我们将其称为 「封闭岛屿」。

请返回封闭岛屿的数目。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/11/07/sample_3_1610.png
输入：grid = [
	[1,1,1,1,1,1,1,0],
	[1,0,0,0,0,1,1,0],
	[1,0,1,0,1,1,1,0],
	[1,0,0,0,0,1,0,1],
	[1,1,1,1,1,1,1,0],
]
输出：2
解释：
灰色区域的岛屿是封闭岛屿，因为这座岛屿完全被水域包围（即被 1 区域包围）。

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/11/07/sample_4_1610.png
输入：grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
输出：1

示例 3：
输入：grid = [
	[1,1,1,1,1,1,1],
	[1,0,0,0,0,0,1],
	[1,0,1,1,1,0,1],
	[1,0,1,0,1,0,1],
	[1,0,1,1,1,0,1],
	[1,0,0,0,0,0,1],
	[1,1,1,1,1,1,1],
]
输出：2

提示：
	1 <= grid.length, grid[0].length <= 100
	0 <= grid[i][j] <=1
*/


class Solution
{
	vector<vector<int>> grid;
	int rows, cols;
	vector<pair<int, int>> cur, nxt;

	void bfs(int h, int w)
	{
		int const dirs[] = { -1, 0, 1, 0, -1 };
		int val = grid[h][w];
		cur.clear();
		cur.push_back({ h, w });
		grid[h][w] = 1 - val;
		while (!cur.empty())
		{
			nxt.clear();
			for (pair<int, int> p : cur)
				for (int d = 0; d < 4; ++d)
				{
					h = p.first + dirs[d];
					w = p.second + dirs[d + 1];
					if (static_cast<unsigned>(h) < static_cast<unsigned>(rows)
						&& static_cast<unsigned>(w) < static_cast<unsigned>(cols)
						&& grid[h][w] == val)
					{
						nxt.push_back({ h, w });
						grid[h][w] = 1 - val;
					}
				}
			nxt.swap(cur);
		}
	}

public:
	int closedIsland(vector<vector<int>>& _grid)
	{
		int sum = 0;
		grid.swap(_grid);
		rows = static_cast<int>(grid.size());
		cols = static_cast<int>(grid[0].size());

		for (int w = 0; w < cols; ++w)
		{
			if (grid[0][w] == 0)
				bfs(0, w);
			if (grid[rows - 1][w] == 0)
				bfs(rows - 1, w);
		}
		for (int h = 1; h < rows - 1; ++h)
		{
			if (grid[h][0] == 0)
				bfs(h, 0);
			if (grid[h][cols - 1] == 0)
				bfs(h, cols - 1);
		}

		for (int h = 1; h < rows - 1; ++h)
			for (int w = 1; w < cols - 1; ++w)
				if (grid[h][w] == 0)
				{
					++sum;
					bfs(h, w);
				}
		return sum;
	}
};


int main()
{}
