#include "leetcode.hpp"

/* 1568. 使陆地分离的最少天数

给你一个由若干 0 和 1 组成的二维网格 grid ，其中 0 表示水，而 1 表示陆地。
岛屿由水平方向或竖直方向上相邻的 1 （陆地）连接形成。

如果 恰好只有一座岛屿 ，则认为陆地是 连通的 ；否则，陆地就是 分离的 。

一天内，可以将任何单个陆地单元（1）更改为水单元（0）。

返回使陆地分离的最少天数。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/30/1926_island.png
https://assets.leetcode.com/uploads/2020/08/13/1926_island.png
输入：grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
输出：2
解释：至少需要 2 天才能得到分离的陆地。
将陆地 grid[1][1] 和 grid[0][2] 更改为水，得到两个分离的岛屿。

示例 2：

输入：grid = [[1,1]]
输出：2
解释：如果网格中都是水，也认为是分离的 ([[1,1]] -> [[0,0]])，0 岛屿。

示例 3：

输入：grid = [[1,0,1,0]]
输出：0

示例 4：

输入：grid = [
	[1,1,0,1,1],
	[1,1,1,1,1],
	[1,1,0,1,1],
	[1,1,0,1,1]
]
输出：1

示例 5：

输入：grid = [
	[1,1,0,1,1],
	[1,1,1,1,1],
	[1,1,0,1,1],
	[1,1,1,1,1]
]
输出：2

提示：
	1 <= grid.length, grid[i].length <= 30
	grid[i][j] 为 0 或 1
*/

// 看的别人答案
// 没有意识到答案只有 0 1 2 三种情况
class Solution
{
	char visit[30][30];

	int numIsland(vector<vector<int>>& grid)
	{
		int num = 0;
		int rows = static_cast<int>(grid.size());
		int cols = static_cast<int>(grid[0].size());
		int dirs[] = { -1, 0, 1, 0, -1 };
		vector<pair<int, int>> curr, temp;
		memset(visit, 0, sizeof(visit));
		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
			{
				if ((grid[h][w] == 0) || visit[h][w])
					continue;
				curr.emplace_back(h, w);
				visit[h][w] = 1;
				while (!curr.empty())
				{
					temp.clear();
					for (auto& p : curr)
						for (int i = 0; i < 4; ++i)
						{
							int y = p.first + dirs[i];
							int x = p.second + dirs[i + 1];
							if (((unsigned)(y) >= (unsigned)(rows))
								|| ((unsigned)(x) >= (unsigned)(cols))
								|| visit[y][x]
								|| (grid[y][x] == 0))
								continue;
							visit[y][x] = 1;
							temp.emplace_back(y, x);
						}
					temp.swap(curr);
				}
				++num;
			}
		return num;
	}

public:
	int minDays(vector<vector<int>>& grid)
	{
		int n = numIsland(grid);
		if (n != 1)
			return 0;
		int rows = static_cast<int>(grid.size());
		int cols = static_cast<int>(grid[0].size());
		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
			{
				if (grid[h][w] == 0)
					continue;
				grid[h][w] = 0;
				n = numIsland(grid);
				if (n != 1)
					return 1;
				grid[h][w] = 1;
			}
		return 2;
	}
};


int main()
{}
