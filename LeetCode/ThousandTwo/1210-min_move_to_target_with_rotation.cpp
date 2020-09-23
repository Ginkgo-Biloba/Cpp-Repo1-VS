#include "leetcode.hpp"

/* 1210. 穿过迷宫的最少移动次数

你还记得那条风靡全球的贪吃蛇吗？

我们在一个 n*n 的网格上构建了新的迷宫地图，蛇的长度为 2，也就是说它会占去两个单元格。
蛇会从左上角（(0, 0) 和 (0, 1)）开始移动。
我们用 0 表示空单元格，用 1 表示障碍物。蛇需要移动到迷宫的右下角（(n-1, n-2) 和 (n-1, n-1)）。

每次移动，蛇可以这样走：
	如果没有障碍，则向右移动一个单元格。并仍然保持身体的水平／竖直状态。
	如果没有障碍，则向下移动一个单元格。并仍然保持身体的水平／竖直状态。
	如果它处于水平状态并且其下面的两个单元都是空的，就顺时针旋转 90 度。
		蛇从（(r, c)、(r, c+1)）移动到 （(r, c)、(r+1, c)）。
	如果它处于竖直状态并且其右面的两个单元都是空的，就逆时针旋转 90 度。
		蛇从（(r, c)、(r+1, c)）移动到（(r, c)、(r, c+1)）。

返回蛇抵达目的地所需的最少移动次数。

如果无法到达目的地，请返回 -1。

示例 1：
输入：grid = [[0,0,0,0,0,1],
							[1,1,0,0,1,0],
							[0,0,0,0,1,1],
							[0,0,1,0,1,0],
							[0,1,1,0,0,0],
							[0,1,1,0,0,0]]
输出：11
解释：
一种可能的解决方案是 [右, 右, 顺时针旋转, 右, 下, 下, 下, 下, 逆时针旋转, 右, 下]。

示例 2：
输入：grid = [[0,0,1,1,1,1],
							[0,0,0,0,1,1],
							[1,1,0,0,0,1],
							[1,1,1,0,0,1],
							[1,1,1,0,0,1],
							[1,1,1,0,0,0]]
输出：9

提示：
	2 <= n <= 100
	0 <= grid[i][j] <= 1
	蛇保证从空单元格开始出发。
*/

class Solution
{
	vector<vector<int>> grid;
	vector<pair<int, int>> cur, buf;
	int len;

	bool check(pair<int, int> const& q)
	{
		bool inside = false;
		int x = q.first, y = q.second;
		// face down
		if (x < 0)
		{
			x = -1 - x;
			inside = (x < len) && (y < len - 1)
				&& !(grid[y][x] & 1) && !(grid[y + 1][x] & 1)
				&& !(grid[y][x] & 2);
		}
		// face right
		else
		{
			inside = (x < len - 1) && (y < len)
				&& !(grid[y][x] & 1) && !(grid[y][x + 1] & 1)
				&& !(grid[y][x] & 4);
		}
		if (inside)
		{
			buf.push_back(q);
			// https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/discuss/392872/C%2B%2B-BFS
			grid[y][x] |= (q.first < 0) ? 2 : 4;
		}
		return (q.first == len - 2) && (q.second == len - 1);
	}

public:
	int minimumMoves(vector<vector<int>>& G)
	{
		grid.swap(G);
		len = static_cast<int>(grid.size());
		pair<int, int> q(0, 0);
		cur.clear();
		cur.emplace_back(q);
		for (int step = 1; !cur.empty(); ++step)
		{
			buf.clear();
			for (pair<int, int> const& p : cur)
			{
				// right
				q.first = p.first + (p.first < 0 ? -1 : 1);
				q.second = p.second;
				if (check(q)) return step;
				// down
				q.first = p.first;
				q.second = p.second + 1;
				if (check(q)) return step;
				// rotate, impossilbe to be answer
				q.first = -1 - p.first;
				q.second = p.second;
				int x1 = max(q.first, p.first) + 1;
				int y1 = q.second + 1;
				if ((x1 < len) && (y1 < len) && !(grid[x1][y1]))
					check(q);
			}
			buf.swap(cur);
		}
		return -1;
	}
};


int main()
{
	vector<vector<int>>
		a = {
			{ 0, 0, 0, 0, 0, 1 },
			{ 1, 1, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 1, 1 },
			{ 0, 0, 1, 0, 1, 0 },
			{ 0, 1, 1, 0, 0, 0 },
			{ 0, 1, 1, 0, 0, 0 },
	},
	b = {
		{ 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 0 },
	},
	c = {
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	Solution s;
	OutExpr(s.minimumMoves(a), "%d");
	OutExpr(s.minimumMoves(b), "%d");
	OutExpr(s.minimumMoves(c), "%d");
}
