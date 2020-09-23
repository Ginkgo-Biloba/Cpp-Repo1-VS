#include "leetcode.hpp"

/* 463. 岛屿的周长
给定一个包含 0 和 1 的二维网格地图，其中 1 表示陆地 0 表示水域。

网格中的格子水平和垂直方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。

岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

示例 :
输入:
[[0,1,0,0},
 [1,1,1,0},
 [0,1,0,0},
 [1,1,0,0}}
输出: 16

解释: 它的周长是下面图片中的 16 个黄色的边：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/island.png
https://assets.leetcode.com/uploads/2018/10/12/island.png
*/

int islandPerimeter(vector<vector<int>>& grid)
{
	int const xdir[4] = { 0, -1, 1, 0 };
	int const ydir[4] = { -1, 0, 0, 1 };
	int perimeter = 0;
	unsigned rows = grid.size();
	if (rows == 0)
		return 0;
	unsigned cols = grid[0].size();

	for (unsigned h = 0; h < rows; ++h)
	{
		int const* ptr = grid[h].data();
		for (unsigned w = 0; w < cols; ++w)
		{
			if (ptr[w] == 0)
				continue;
			for (int d = 0; d < 4; ++d)
			{
				unsigned dy = h + ydir[d];
				unsigned dx = w + xdir[d];
				if (dy >= rows || dx >= cols || grid[dy][dx] == 0)
					++perimeter;
			}
		}
	}

	return perimeter;
}


int main()
{
	vector<vector<int>> grid =
	{
		{ 0, 1, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 }
	};
	OutExpr(islandPerimeter(grid), "%d");
}
