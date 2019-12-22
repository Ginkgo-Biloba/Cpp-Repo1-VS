#include "leetcode.hpp"

/* 827. 最大人工岛

在二维地图上， 0代表海洋， 1代表陆地，我们最多只能将一格 0 海洋变成 1变成陆地。

进行填海之后，地图上最大的岛屿面积是多少？（上、下、左、右四个方向相连的 1 可形成岛屿）

示例 1:
输入: [[1, 0], [0, 1]]
输出: 3
解释: 将一格0变成1，最终连通两个小岛得到面积为 3 的岛屿。

示例 2:
输入: [[1, 1], [1, 0]]
输出: 4
解释: 将一格0变成1，岛屿的面积扩大为 4。

示例 3:
输入: [[1, 1], [1, 1]]
输出: 4
解释: 没有0可以让我们变成1，面积依然为 4。

说明:
	1 <= grid.length = grid[0].length <= 50
	0 <= grid[i][j] <= 1
*/

int merge(int y, int x)
{
	return (y << 16) | (x & USHRT_MAX);
}

void split(int i, int& y, int& x)
{
	// 注意符号扩展，虽然这个问题里面不会出现
	y = static_cast<short>(i >> 16);
	x = static_cast<short>(i & USHRT_MAX);
}

int largestIsland(vector<vector<int>>& grid)
{
	int const dirs[] = { -1, 0, 1, 0, -1 };
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	int max1s = 0, ids = -1;
	int neighbor[4], nn;
	vector<int> pts, count;
	pts.reserve(rows * cols);

	for (int h = 0; h != rows; ++h)
		for (int w = 0; w != cols; ++w)
		{
			if (grid[h][w] != 1)
				continue;
			pts.clear();
			pts.push_back(merge(h, w));
			grid[h][w] = ids;
			int y, x, cy, cx;
			for (size_t ip = 0; ip < pts.size(); ++ip)
			{
				split(pts[ip], y, x);
				for (int d = 0; d < 4; ++d)
				{
					cy = y + dirs[d];
					cx = x + dirs[d + 1];
					if (static_cast<unsigned>(cy) >= static_cast<unsigned>(rows)
						|| static_cast<unsigned>(cx) >= static_cast<unsigned>(cols)
						|| grid[cy][cx] <= 0)
						continue;
					pts.push_back(merge(cy, cx));
					grid[cy][cx] = ids;
				}
			}
			x = static_cast<int>(pts.size());
			count.push_back(x);
			max1s = std::max(max1s, x);
			--ids;
		}

	for (int h = 0; h != rows; ++h)
		for (int w = 0; w != cols; ++w)
		{
			if (grid[h][w] != 0)
				continue;
			int y, x, n, m1 = 1;
			nn = 0;
			for (int d = 0; d < 4; ++d)
			{
				y = h + dirs[d];
				x = w + dirs[d + 1];
				if (static_cast<unsigned>(y) >= static_cast<unsigned>(rows)
					|| static_cast<unsigned>(x) >= static_cast<unsigned>(cols)
					|| grid[y][x] == 0)
					continue;
				ids = grid[y][x];
				for (n = 0; n < nn; ++n)
				{
					if (neighbor[n] == ids)
						break;
				}
				if (n == nn)
				{
					m1 += count[-1 - ids];
					neighbor[nn] = ids;
					++nn;
				}
			}
			max1s = std::max(max1s, m1);
		}

	return max1s;
}


int main()
{
	vector<vector<int>>
		g0 = { { 1, 0 }, { 0, 1 } },
		g1 = { { 1, 1 }, { 1, 0 } },
		g2 = { { 1, 1 }, { 1, 1 } };
	OutExpr(largestIsland(g0), "%d");
	OutExpr(largestIsland(g1), "%d");
	OutExpr(largestIsland(g2), "%d");
}
