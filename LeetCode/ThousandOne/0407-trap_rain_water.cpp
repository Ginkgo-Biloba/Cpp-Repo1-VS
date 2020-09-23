#include "leetcode.hpp"

/* 407. 接雨水 II

给定一个 m x n 的矩阵，其中的值均为正整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。

说明:
m 和 n 都是小于 110 的整数。每一个单位的高度都大于 0 且小于 20000。

示例：

给出如下 3x6 的高度图:
[
[1,4,3,1,3,2],
[3,2,1,3,2,4],
[2,3,3,2,3,1]
]

返回 4。
*/

// https://leetcode.com/problems/trapping-rain-water-ii/discuss/89495/How-to-get-the-solution-to-2-D-%22Trapping-Rain-Water%22-problem-from-1-D-case
// 抄的

class Solution
{
	int rows, cols, acml;
	vector<char> visit;

	struct cell
	{
		int y, x, h;
		cell(int _y, int _x, int _h) : y(_y), x(_x), h(_h) {}
		cell(cell const&) = default;
		cell& operator =(cell const&) = default;
		bool operator <(cell const& c) const { return h > c.h; }
	};

	int at(int y, int x)
	{
		return y * cols + x;
	}

public:
	int trapRainWater(vector<vector<int>>& hmap)
	{
		rows = static_cast<int>(hmap.size());
		if (rows == 0 || hmap[0].empty())
			return 0;
		cols = static_cast<int>(hmap[0].size());
		acml = rows * cols;
		if (visit.size() < static_cast<unsigned>(acml))
			visit.resize(acml);
		memset(visit.data(), 0, acml * sizeof(char));
		acml = 0;

		int const ys[4] = { -1, 0, 0, 1 };
		int const xs[4] = { 0, -1, 1, 0 };
		std::priority_queue<cell> q;
		for (int w = 0; w < cols; ++w)
		{
			q.emplace(0, w, hmap[0][w]);
			q.emplace(rows - 1, w, hmap[rows - 1][w]);
			visit[at(0, w)] = visit[at(rows - 1, w)] = 1;
		}
		for (int h = 1; h < rows - 1; ++h)
		{
			q.emplace(h, 0, hmap[h][0]);
			q.emplace(h, cols - 1, hmap[h][cols - 1]);
			visit[at(h, 0)] = visit[at(h, cols - 1)] = 1;
		}

		while (!q.empty())
		{
			cell cur = q.top();
			q.pop();
			for (int i = 0; i < 4; ++i)
			{
				int x = cur.x + xs[i];
				int y = cur.y + ys[i];
				if (static_cast<unsigned>(y) >= static_cast<unsigned>(rows)
					|| static_cast<unsigned>(x) >= static_cast<unsigned>(cols)
					|| visit[at(y, x)])
					continue;
				int h = hmap[y][x];
				acml += std::max(0, cur.h - h);
				q.emplace(y, x, std::max(cur.h, h));
				visit[at(y, x)] = 1;
			}
		}

		return acml;
	}
};


int main()
{
	vector<vector<int>> hmap = {
		{ 1, 4, 3, 1, 3, 2 },
		{ 3, 2, 1, 3, 2, 4 },
		{ 2, 3, 3, 2, 3, 1 }
	};
	OutExpr(Solution().trapRainWater(hmap), "%d");
};


