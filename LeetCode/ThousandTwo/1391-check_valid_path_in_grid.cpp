#include "leetcode.hpp"

/* 1391. 检查网格中是否存在有效路径

给你一个 m x n 的网格 grid。
网格里的每个单元都代表一条街道。grid[i][j] 的街道可以是：
	1 表示连接左单元格和右单元格的街道。
	2 表示连接上单元格和下单元格的街道。
	3 表示连接左单元格和下单元格的街道。
	4 表示连接右单元格和下单元格的街道。
	5 表示连接左单元格和上单元格的街道。
	6 表示连接右单元格和上单元格的街道。

你最开始从左上角的单元格 (0,0) 开始出发，网格中的「有效路径」是指从左上方的单元格 (0,0) 开始、一直到右下方的 (m-1,n-1) 结束的路径。
该路径必须只沿着街道走。

注意：你 不能 变更街道。

如果网格中存在有效的路径，则返回 true，否则返回 false 。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/03/21/main.png
输入：grid = [[2,4,3],[6,5,2]]
输出：true
解释：如图所示，你可以从 (0, 0) 开始，访问网格中的所有单元格并到达 (m - 1, n - 1) 。

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/03/21/e1.png
输入：grid = [[1,2,1],[1,2,1]]
输出：false
解释：如图所示，单元格 (0, 0) 上的街道没有与任何其他单元格上的街道相连，你只会停在 (0, 0) 处。

示例 3：
输入：grid = [[1,1,2]]
输出：false
解释：你会停在 (0, 1)，而且无法到达 (0, 2) 。

示例 4：
输入：grid = [[1,1,1,1,1,1,3]]
输出：true

示例 5：
输入：grid = [[2],[2],[2],[2],[2],[2],[6]]
输出：true

提示：
	m == grid.length
	n == grid[i].length
	1 <= m, n <= 300
	1 <= grid[i][j] <= 6
*/

// 顺时针旋转，上右下左上右
static int const mask[7] = {
	0b000000,
	0b010101,
	0b101010,
	0b001100,
	0b011001,
	0b100110,
	0b110011,
};

static int const dirs[5] = { -1, 0, 1, 0, -1 };

class Solution
{
	char visit[300][300];

public:
	bool hasValidPath(vector<vector<int>>& grid)
	{
		int rows = static_cast<int>(grid.size());
		int cols = static_cast<int>(grid[0].size());
		vector<pair<int, int>> current, nextloop;
		memset(visit, 0, sizeof(visit));
		current.emplace_back(0, 0);
		visit[0][0] = 1;
		while (!current.empty())
		{
			nextloop.clear();
			for (pair<int, int> cur : current)
				for (int d = 0; d < 4; ++d)
				{
					int h = cur.first + dirs[d];
					int w = cur.second + dirs[d + 1];
					if (static_cast<unsigned>(h) >= static_cast<unsigned>(rows)
						|| static_cast<unsigned>(w) >= static_cast<unsigned>(cols)
						|| visit[h][w])
						continue;
					int a = mask[grid[cur.first][cur.second]] & (1 << (5 - d));
					int b = mask[grid[h][w]] & (1 << (3 - d));
					if (a && b)
					{
						nextloop.emplace_back(h, w);
						visit[h][w] = 1;
					}
				}
			nextloop.swap(current);
		}
		return visit[rows - 1][cols - 1] != 0;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 2, 4, 3 }, { 6, 5, 2 } },
		b = { { 1, 2, 1 }, { 1, 2, 1 } },
		c = { { 1, 1, 2 } },
		d = { { 1, 1, 1, 1, 1, 1, 3 } },
		e = { { 2 }, { 2 }, { 2 }, { 2 }, { 2 }, { 2 }, { 6 } };
	Solution s;
	OutBool(s.hasValidPath(a));
	OutBool(s.hasValidPath(b));
	OutBool(s.hasValidPath(c));
	OutBool(s.hasValidPath(d));
	OutBool(s.hasValidPath(e));
}
