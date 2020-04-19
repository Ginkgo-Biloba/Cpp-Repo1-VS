#include "leetcode.hpp"

/* 1293. 网格中的最短路径

给你一个 m * n 的网格，其中每个单元格不是 0（空）就是 1（障碍物）。
每一步，您都可以在空白单元格中上、下、左、右移动。

如果您 最多 可以消除 k 个障碍物，请找出从左上角 (0, 0) 到右下角 (m-1, n-1) 的最短路径，并返回通过该路径所需的步数。

如果找不到这样的路径，则返回 -1。

示例 1：
输入：
grid =
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]],
k = 1
输出：6
解释：
不消除任何障碍的最短路径是 10。
消除位置 (3,2) 处的障碍后，最短路径是 6 。
该路径是 (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).

示例 2：
输入：
grid =
[[0,1,1],
 [1,1,1],
 [1,0,0]],
k = 1
输出：-1
解释：
我们至少需要消除两个障碍才能找到这样的路径。

提示：
	grid.length == m
	grid[0].length == n
	1 <= m, n <= 40
	1 <= k <= m*n
	grid[i][j] == 0 or 1
	grid[0][0] == grid[m-1][n-1] == 0
*/


class Solution
{
	struct Point
	{
		int y, x, s;
	};

	int rows, cols;
	vector<char> step;
	vector<Point> current, nextloop;
	vector<vector<int>> grid;

	int ibuf(Point const& p)
	{
		return (p.s * rows + p.y) * cols + p.x;
	}

public:
	int shortestPath(vector<vector<int>>& _grid, int k)
	{
		int const dir[] = { -1, 0, 1, 0, -1 };
		grid.swap(_grid);
		rows = static_cast<int>(grid.size());
		cols = static_cast<int>(grid[0].size());
		if (rows == 1 && cols == 1)
			return 0;
		if (rows == 1)
		{
			for (int w = 0; w < cols; ++w)
				k -= grid[0][w];
			return k >= 0 ? cols - 1 : -1;
		}
		if (cols == 1)
		{
			for (int h = 0; h < rows; ++h)
				k -= grid[h][0];
			return k >= 0 ? rows - 1 : -1;
		}

		step.resize((k + 1) * rows * cols);
		memset(step.data(), 0, step.size() * sizeof(step[0]));
		Point pt = { 0, 0, 0 };
		int ip = ibuf(pt);
		step[ip] = 1;
		current.assign(1, pt);
		for (int dummy = 1; !current.empty(); ++dummy)
		{
			nextloop.clear();
			for (Point cur : current)
				for (int d = 0; d < 4; ++d)
				{
					pt.y = cur.y + dir[d];
					pt.x = cur.x + dir[d + 1];
					if (static_cast<unsigned>(pt.y) >= static_cast<unsigned>(rows)
						|| static_cast<unsigned>(pt.x) >= static_cast<unsigned>(cols))
						continue;
					pt.s = cur.s + grid[pt.y][pt.x];
					if (pt.s > k)
						continue;
					if ((pt.y == rows - 1) && (pt.x == cols - 1))
						return dummy;
					ip = ibuf(pt);
					if (!(step[ip]))
					{
						nextloop.push_back(pt);
						step[ip] = 1;
					}
				}
			nextloop.swap(current);
		}
		return -1;
	}
};


int main()
{
	vector<vector<int>>
		a = {
			{ 0, 0, 0 },
			{ 1, 1, 0 },
			{ 0, 0, 0 },
			{ 0, 1, 1 },
			{ 0, 0, 0 },
	},
	b = {
		{ 0, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 0, 0 },
	};
	Solution s;
	OutExpr(s.shortestPath(a, 1), "%d");
	OutExpr(s.shortestPath(b, 1), "%d");
}
