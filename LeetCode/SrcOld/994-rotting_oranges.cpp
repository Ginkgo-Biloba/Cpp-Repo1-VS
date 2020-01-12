#include "leetcode.hpp"

/* 994. 腐烂的橘子

在给定的网格中，每个单元格可以有以下三个值之一：
	值 0 代表空单元格；
	值 1 代表新鲜橘子；
	值 2 代表腐烂的橘子。

每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。

返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。

示例 1：
输入：[[2,1,1],[1,1,0],[0,1,1]]
输出：4
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/02/16/oranges.png

示例 2：
输入：[[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个正向上。

示例 3：
输入：[[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。

提示：
	1 <= grid.length <= 10
	1 <= grid[0].length <= 10
	grid[i][j] 仅为 0、1 或 2
*/

int orangesRotting(vector<vector<int>>& grid)
{
	int dirs[] = { -1, 0, 1, 0, -1 };
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	int step = 0;
	vector<pair<int, int>> current, nextstep;

	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
		{
			if (grid[h][w] == 2)
				current.emplace_back(h, w);
		}

	while (!current.empty())
	{
		--step;
		nextstep.clear();
		for (pair<int, int> cur : current)
			for (int d = 0; d < 4; ++d)
			{
				int h = cur.first + dirs[d];
				int w = cur.second + dirs[d + 1];
				if (static_cast<unsigned>(h) >= static_cast<unsigned>(rows)
					|| static_cast<unsigned>(w) >= static_cast<unsigned>(cols)
					|| grid[h][w] != 1)
					continue;
				grid[h][w] = step;
				nextstep.emplace_back(h, w);
			}
		nextstep.swap(current);
	}

	step = 0;
	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
		{
			step = min(step, grid[h][w]);
			if (grid[h][w] == 1)
				return -1;
		}
	return -step;
}


int main()
{
	vector<vector<int>>
		a = { { 2, 1, 1 }, { 1, 1, 0 }, { 0, 1, 1 } },
		b = { { 2, 1, 1 }, { 0, 1, 1 }, { 1, 0, 1 } },
		c = { { 0, 2 } };
	OutExpr(orangesRotting(a), "%d");
	OutExpr(orangesRotting(b), "%d");
	OutExpr(orangesRotting(c), "%d");
}
