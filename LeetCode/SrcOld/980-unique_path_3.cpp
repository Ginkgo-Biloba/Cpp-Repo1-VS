#include "leetcode.hpp"

/* 980. 不同路径 III

在二维网格 grid 上，有 4 种类型的方格：
	1 表示起始方格。且只有一个起始方格。
	2 表示结束方格，且只有一个结束方格。
	0 表示我们可以走过的空方格。
	-1 表示我们无法跨越的障碍。

返回在四个方向（上、下、左、右）上行走时，从起始方格到结束方格的不同路径的数目，每一个无障碍方格都要恰好通过一次。
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

示例 1：
输入：[[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
输出：2
解释：我们有以下两条路径：
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

示例 2：
输入：[[1,0,0,0],[0,0,0,0],[0,0,0,2]]
输出：4
解释：我们有以下四条路径：
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

示例 3：
输入：[[0,1],[2,0]]
输出：0
解释：
没有一条路能完全穿过每一个空的方格一次。
请注意，起始和结束方格可以位于网格中的任意位置。

提示：
	1 <= grid.length * grid[0].length <= 20
*/


class Solution
{
	// 踩过哪些格子，最后踩的那个格子
	struct FYX
	{
		int f;
		short y, x;
	};

	int rows, cols, size, plen, fstart;
	unsigned urows, ucols;
	vector<FYX> current, nextstep;
	vector<short> path; // 测试了一下 short 能过。。。
	FYX target;

	int toflag(int y, int x)
	{
		return 1 << (y * cols + x);
	}

	short addto(FYX const& p, short delta)
	{
		// 实质上，起点如果在开始 fstart = 1，跟没有一样
		int i = (p.f - fstart) * size + p.y * cols + p.x;
		path[i] += delta;
		return path[i];
	}

public:
	int uniquePathsIII(vector<vector<int>>& grid)
	{
		int const dirs[5] = { -1, 0, 1, 0, -1 };
		urows = rows = static_cast<int>(grid.size());
		ucols = cols = static_cast<int>(grid[0].size());
		size = rows * cols;

		FYX pos = { 0, 0, 0 };
		target.f = (1 << size) - 1;
		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
			{
				int f = toflag(h, w);
				// 障碍物设置成踩过，省事
				if (grid[h][w] == 1 || grid[h][w] == -1)
				{
					// 起点
					if (grid[h][w] == 1)
					{
						pos.y = static_cast<short>(h);
						pos.x = static_cast<short>(w);
					}
					pos.f |= f;
				}
				else if (grid[h][w] == 2)
				{
					target.y = static_cast<short>(h);
					target.x = static_cast<short>(w);
				};
			}

		fstart = pos.f;
		plen = (1 << size) * size - fstart;
		path.resize(plen);
		memset(path.data(), 0, plen * sizeof(path[0]));

		// 广搜
		current.clear();
		current.push_back(pos);
		addto(pos, 1);
		while (!current.empty())
		{
			nextstep.clear();
			for (auto const& cur : current)
			{
				// 如果 current 没有去重，那么 delta 只能是 1
				// 如果有多条路径到同一状态，那么就会 push_back 多次
				short delta = addto(cur, 0);
				// int delta = 1;
				for (int d = 0; d < 4; ++d)
				{
					int h = cur.y + dirs[d];
					int w = cur.x + dirs[d + 1];
					if (static_cast<unsigned>(h) >= urows
						|| static_cast<unsigned>(w) >= ucols)
						continue;
					int f = toflag(h, w);
					// 已经踩过
					if (cur.f & f)
						continue;
					pos.f = cur.f | f;
					pos.y = static_cast<short>(h);
					pos.x = static_cast<short>(w);
					short p = addto(pos, delta);
					// 是终点的话，无须往前走
					if (pos.y == target.y && pos.x == target.x)
						continue;
					// 如果不去除重复，delta 只能是 1
					// 运行时间差不多扩大为答案的倍数
					// f == delta 说明第一次遇见这个状态
					if (p == delta)
						nextstep.push_back(pos);
				}
			}
			nextstep.swap(current);
		}

		return addto(target, 0);
	}
};


int main()
{
	vector<vector<int>>
		a = { { 1, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 2, -1 } },
		b = { { 1, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 2 } },
		c = { { 0, 1 }, { 2, 0 } },
		d = {
			{ 1, 0, 0, 0, -1 },
			{ 0, 0, 0, 0, -1 },
			{ 0, 0, 0, 0, 0 },
			{ -1, -1, -1, -1, 2 }
	};
	Solution s;
	OutExpr(s.uniquePathsIII(a), "%d");
	OutExpr(s.uniquePathsIII(b), "%d");
	OutExpr(s.uniquePathsIII(c), "%d");
	OutExpr(s.uniquePathsIII(d), "%d");
}
