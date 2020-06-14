#include "leetcode.hpp"

/* 1463. 摘樱桃 II

给你一个 rows x cols 的矩阵 grid 来表示一块樱桃地。
grid 中每个格子的数字表示你能获得的樱桃数目。

你有两个机器人帮你收集樱桃，机器人 1 从左上角格子 (0,0) 出发，机器人 2 从右上角格子 (0, cols-1) 出发。

请你按照如下规则，返回两个机器人能收集的最多樱桃数目：
	从格子 (i,j) 出发，机器人可以移动到格子 (i+1, j-1)，(i+1, j) 或者 (i+1, j+1) 。
	当一个机器人经过某个格子时，它会把该格子内所有的樱桃都摘走，然后这个位置会变成空格子，即没有樱桃的格子。
	当两个机器人同时到达同一个格子时，它们中只有一个可以摘到樱桃。
	两个机器人在任意时刻都不能移动到 grid 外面。
	两个机器人最后都要到达 grid 最底下一行。

示例 1：
https://assets.leetcode.com/uploads/2020/04/29/sample_1_1802.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/30/sample_1_1802.png
输入：grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
输出：24
解释：机器人 1 和机器人 2 的路径在上图中分别用绿色和蓝色表示。
机器人 1 摘的樱桃数目为 (3 + 2 + 5 + 2) = 12 。
机器人 2 摘的樱桃数目为 (1 + 5 + 5 + 1) = 12 。
樱桃总数为： 12 + 12 = 24 。

示例 2：
https://assets.leetcode.com/uploads/2020/04/23/sample_2_1802.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/30/sample_2_1802.png
输入：grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
输出：28
解释：机器人 1 和机器人 2 的路径在上图中分别用绿色和蓝色表示。
机器人 1 摘的樱桃数目为 (1 + 9 + 5 + 2) = 17 。
机器人 2 摘的樱桃数目为 (1 + 3 + 4 + 3) = 11 。
樱桃总数为： 17 + 11 = 28 。

示例 3：
输入：grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
输出：22

示例 4：
输入：grid = [[1,1],[1,1]]
输出：4

提示：
	rows == grid.length
	cols == grid[i].length
	2 <= rows, cols <= 70
	0 <= grid[i][j] <= 100
*/

int cherryPickup(vector<vector<int>>& grid)
{
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	unsigned ucols = cols;
	vector<array<int, 70>> cur(cols), tmp(cols);
	size_t line = cols * sizeof(cur[0]);

	memset(cur.data(), 0xff, line);
	cur[0][cols - 1] = grid[0][0] + grid[0][cols - 1];
	for (int h = 1; h < rows; ++h)
	{
		int const* ptr = grid[h].data();
		memset(tmp.data(), 0xff, line);
		for (int a = 0; a < cols; ++a)
			for (int b = a + 1; b < cols; ++b)
			{
				if (cur[a][b] < 0)
					continue;
				for (int p = -1; p <= 1; ++p)
					for (int q = -1; q <= 1; ++q)
					{
						unsigned c = a + p;
						unsigned d = b + q;
						if ((d <= c) || (c >= ucols) || (d >= ucols))
							continue;
						int e = ptr[c] + ptr[d] + cur[a][b];
						tmp[c][d] = max(tmp[c][d], e);
					}
			}
		cur.swap(tmp);
	}

	int ans = 0;
	for (int a = 0; a < cols; ++a)
		for (int b = a + 1; b < cols; ++b)
			ans = max(ans, cur[a][b]);
	return ans;
}


int main()
{
	vector<vector<int>>
		a = {
			{ 3, 1, 1 },
			{ 2, 5, 1 },
			{ 1, 5, 5 },
			{ 2, 1, 1 },
	},
	b = {
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 2, 0, 0, 0, 0, 3, 0 },
		{ 2, 0, 9, 0, 0, 0, 0 },
		{ 0, 3, 0, 5, 4, 0, 0 },
		{ 1, 0, 2, 3, 0, 0, 6 },
	},
	c = {
		{ 1, 0, 0, 3 },
		{ 0, 0, 0, 3 },
		{ 0, 0, 3, 3 },
		{ 9, 0, 3, 3 },
	},
	d = {
		{ 1, 1 },
		{ 1, 1 },
	},
	e = {
		{ 0, 8, 7, 10, 9, 10, 0, 9, 6 },
		{ 8, 7, 10, 8, 7, 4, 9, 6, 10 },
		{ 8, 1, 1, 5, 1, 5, 5, 1, 2 },
		{ 9, 4, 10, 8, 8, 1, 9, 5, 0 },
		{ 4, 3, 6, 10, 9, 2, 4, 8, 10 },
		{ 7, 3, 2, 8, 3, 3, 5, 9, 8 },
		{ 1, 2, 6, 5, 6, 2, 0, 10, 0 },
	};
	OutExpr(cherryPickup(a), "%d");
	OutExpr(cherryPickup(b), "%d");
	OutExpr(cherryPickup(c), "%d");
	OutExpr(cherryPickup(d), "%d");
	OutExpr(cherryPickup(e), "%d");
}
