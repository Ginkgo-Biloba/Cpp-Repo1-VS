#include "leetcode.hpp"

/* 1617. 统计子树中城市之间最大距离

给你 n 个城市，编号为从 1 到 n 。
同时给你一个大小为 n-1 的数组 edges ，其中 edges[i] = [ui, vi] 表示城市 ui 和 vi 之间有一条双向边。
题目保证任意城市之间只有唯一的一条路径。
换句话说，所有城市形成了一棵 树 。

一棵 子树 是城市的一个子集，且子集中任意城市之间可以通过子集中的其他城市和边到达。
两个子树被认为不一样的条件是至少有一个城市在其中一棵子树中存在，但在另一棵子树中不存在。

对于 d 从 1 到 n-1 ，请你找到城市间 最大距离 恰好为 d 的所有子树数目。

请你返回一个大小为 n-1 的数组，其中第 d 个元素（下标从 1 开始）是城市间 最大距离 恰好等于 d 的子树数目。

请注意，两个城市间距离定义为它们之间需要经过的边的数目。

示例 1：
https://assets.leetcode.com/uploads/2020/09/21/p1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/11/p1.png
输入：n = 4, edges = [[1,2],[2,3],[2,4]]
输出：[3,4,0]
解释：
子树 {1,2}, {2,3} 和 {2,4} 最大距离都是 1 。
子树 {1,2,3}, {1,2,4}, {2,3,4} 和 {1,2,3,4} 最大距离都为 2 。
不存在城市间最大距离为 3 的子树。

示例 2：
输入：n = 2, edges = [[1,2]]
输出：[1]

示例 3：
输入：n = 3, edges = [[1,2],[2,3]]
输出：[2,1]

提示：
	2 <= n <= 15
	edges.length == n-1
	edges[i].length == 2
	1 <= ui, vi <= n
	题目保证 (ui, vi) 所表示的边互不相同。
*/

class Solution
{
	int n;
	int A[16][16], dis[16], pre[16];
	vector<int> ans;
	vector<int> cur, tmp;

	void bfs(int from)
	{
		dis[from] = 0;
		cur.push_back(from);
		while (cur.size())
		{
			tmp.clear();
			for (int i : cur)
			{
				int d = dis[i] + 1;
				int k = A[i][0];
				int* G = A[i] + 1;
				while (k--)
					if (dis[G[k]] > d)
					{
						dis[G[k]] = d;
						tmp.push_back(G[k]);
					}
			}
			tmp.swap(cur);
		}
	}

	void subtree(int mask)
	{
		// 只有一个城市
		if (!(mask & (mask - 1)))
			return;

		int idx = -1;
		for (int i = 0; i < n; ++i)
		{
			if (mask & (1 << i))
			{
				pre[i] = n + 1;
				idx = i;
			}
			else
				pre[i] = -1;
		}
		memcpy(dis, pre, sizeof(pre));
		bfs(idx);
		for (int i = 0; i < n; ++i)
		{
			if (dis[i] < 0)
				continue;
			if (dis[i] > n)
				return;
			if (dis[i] > dis[idx])
				idx = i;
		}
		memcpy(dis, pre, sizeof(pre));
		bfs(idx);
		idx = 0;
		for (int i = 0; i < n; ++i)
			idx = max(idx, dis[i]);
		ans[idx - 1] += 1;
	}

public:
	vector<int> countSubgraphsForEachDiameter(
		int _n, vector<vector<int>>& edges)
	{
		n = _n;
		int mask = 1 << n;
		memset(A, 0, sizeof(A));
		for (auto& e : edges)
		{
			int f = e[0] - 1;
			int t = e[1] - 1;
			A[f][0] += 1;
			A[t][0] += 1;
			A[f][A[f][0]] = t;
			A[t][A[t][0]] = f;
		}
		ans.resize(n - 1);
		cur.reserve(16);
		tmp.reserve(16);
		for (--mask; mask > 0; --mask)
			subtree(mask);
		return std::move(ans);
	}
};


int main()
{
	vector<vector<int>>
		a = { { 1, 2 }, { 2, 3 }, { 2, 4 } },
		b = { { 1, 2 } },
		c = { { 1, 2 }, { 2, 3 } };
	Solution s;
	output(s.countSubgraphsForEachDiameter(4, a), "Subtree");
	output(s.countSubgraphsForEachDiameter(2, b), "Subtree");
	output(s.countSubgraphsForEachDiameter(3, c), "Subtree");
}
