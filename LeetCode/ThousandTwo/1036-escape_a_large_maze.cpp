#include "leetcode.hpp"

/* 1036. 逃离大迷宫

在一个 10^6 x 10^6 的网格中，每个网格块的坐标为 (x, y)，其中 0 <= x, y < 10^6。

我们从源方格 source 开始出发，意图赶往目标方格 target。
每次移动，我们都可以走到网格中在四个方向上相邻的方格，只要该方格不在给出的封锁列表 blocked 上。

只有在可以通过一系列的移动到达目标方格时才返回 true。否则，返回 false。

示例 1：
输入：blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
输出：false
解释：
从源方格无法到达目标方格，因为我们无法在网格中移动。

示例 2：
输入：blocked = [], source = [0,0], target = [999999,999999]
输出：true
解释：
因为没有方格被封锁，所以一定可以到达目标方格。

提示：
	0 <= blocked.length <= 200
	blocked[i].length == 2
	0 <= blocked[i][j] < 10^6
	source.length == target.length == 2
	0 <= source[i][j], target[i][j] < 10^6
	source != target
*/


class Solution
{
	size_t limit;
	unordered_set<uint64_t> forbid, visit;
	vector<pair<int, int>> current, nextstep;

	uint64_t makeKey(int y, int x)
	{
		unsigned uy = y, ux = x;
		return static_cast<uint64_t>(uy)
			| (static_cast<uint64_t>(ux) << 32);
	}

	bool bfs(vector<int>& src, vector<int>& target)
	{
		unsigned const len = 1e6;
		int const dirs[5] = { -1, 0, 1, 0, -1 };
		pair<int, int> pos(src[0], src[1]);
		uint64_t key = makeKey(src[0], src[1]);
		uint64_t dst = makeKey(target[0], target[1]);
		current.clear();
		current.push_back(pos);
		visit.clear();
		visit.insert(key);
		while (!current.empty() && visit.size() < limit)
		{
			nextstep.clear();
			for (auto cur : current)
				for (int d = 0; d < 4; ++d)
				{
					pos.first = cur.first + dirs[d + 1];
					pos.second = cur.second + dirs[d];
					key = makeKey(pos.first, pos.second);
					if (static_cast<unsigned>(pos.first) < len
						&& static_cast<unsigned>(pos.second) < len
						&& forbid.find(key) == forbid.end()
						&& visit.insert(key).second)
						nextstep.push_back(pos);
					if (key == dst)
						return true;
				}
			nextstep.swap(current);
		}
		return visit.size() >= limit;
	}

public:
	bool isEscapePossible(vector<vector<int>>& blocked,
		vector<int>& source, vector<int>& target)
	{
		forbid.clear();
		for (auto const& b : blocked)
			forbid.insert(makeKey(b[0], b[1]));
		limit = forbid.size();
		limit = limit * limit / 2;
		return bfs(source, target) && bfs(target, source);
	}
};


int main()
{
	vector<vector<int>>
		b0 = { { 0, 1 }, { 1, 0 } },
		b1;
	vector<int>
		s0 = { 0, 0 },
		d0 = { 0, 2 },
		s1 = { 0, 0 },
		d1 = { 999999, 999999 };
	Solution s;
	OutBool(s.isEscapePossible(b0, s0, d0));
	OutBool(s.isEscapePossible(b1, s1, d1));
}
