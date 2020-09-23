#include "leetcode.hpp"

/* 1489. 找到最小生成树里的关键边和伪关键边

给你一个 n 个点的带权无向连通图，节点编号为 0 到 n-1 ，同时还有一个数组 edges ，其中 edges[i] = [fromi, toi, weighti] 表示在 fromi 和 toi 节点之间有一条带权无向边。
最小生成树 (MST) 是给定图中边的一个子集，它连接了所有节点且没有环，而且这些边的权值和最小。

请你找到给定图中最小生成树的所有关键边和伪关键边。
如果最小生成树中删去某条边，会导致最小生成树的权值和增加，那么我们就说它是一条关键边。
伪关键边则是可能会出现在某些最小生成树中但不会出现在所有最小生成树中的边。

请注意，你可以分别以任意顺序返回关键边的下标和伪关键边的下标。

示例 1：
https://assets.leetcode.com/uploads/2020/06/04/ex1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/21/ex1.png
输入：n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
输出：[[0,1],[2,3,4,5]]
解释：上图描述了给定图。
下图是所有的最小生成树。
https://assets.leetcode.com/uploads/2020/06/04/msts.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/21/msts.png

注意到第 0 条边和第 1 条边出现在了所有最小生成树中，所以它们是关键边，我们将这两个下标作为输出的第一个列表。
边 2，3，4 和 5 是所有 MST 的剩余边，所以它们是伪关键边。
我们将它们作为输出的第二个列表。

示例 2 ：
https://assets.leetcode.com/uploads/2020/06/04/ex2.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/21/ex2.png
输入：n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
输出：[[],[0,1,2,3]]
解释：可以观察到 4 条边都有相同的权值，任选它们中的 3 条可以形成一棵 MST 。所以 4 条边都是伪关键边。

提示：
	2 <= n <= 100
	1 <= edges.length <= min(200, n * (n - 1) / 2)
	edges[i].length == 3
	0 <= fromi < toi < n
	1 <= weighti <= 1000
	所有 (fromi, toi) 数对都是互不相同的。
*/

// 抄的
class Solution
{
	vector<vector<int>> edges;
	vector<int> par, buf;
	int n, len;

	int find(int x)
	{
		if (x == par[x])
			return x;
		int i = 0;
		while (x != par[x])
		{
			buf[i++] = x;
			x = par[x];
		}
		while (--i >= 0)
			par[buf[i]] = x;
		return x;
	}

	void merge(int a, int b)
	{
		if (a != b)
			par[max(a, b)] = min(a, b);
	}

	int MST(int zero)
	{
		int sum = 0;
		for (int i = 0; i < n; ++i)
			par[i] = i;
		if (zero >= 0)
		{
			int const* e = edges[zero].data();
			sum = e[2];
			merge(e[0], e[1]);
		}
		for (int i = 0; i < len; ++i)
		{
			int const* e = edges[i].data();
			if (e[2] <= 0 || i == zero)
				continue;
			int a = e[0], b = e[1];
			a = find(a);
			b = find(b);
			if (a != b)
			{
				merge(a, b);
				sum += e[2];
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (find(i) != 0)
				return INT_MAX;
		}
		return sum;
	}

public:
	vector<vector<int>> findCriticalAndPseudoCriticalEdges(int _n,
		vector<vector<int>>& _edges)
	{
		n = _n;
		edges.swap(_edges);
		len = static_cast<int>(edges.size());
		par.resize(n);
		buf.resize(n);
		for (int i = 0; i < len; ++i)
			edges[i].push_back(i);
		sort(edges.begin(), edges.end(),
			[](vector<int> const& a, vector<int> const& b) -> bool
		{
			return a[2] < b[2];
		});

		vector<vector<int>> R(2);
		int cur, best = MST(-1);
		// 从后往前，尽早删除掉长边 (?)
		for (int i = len - 1; i >= 0; --i)
		{
			int* e = edges[i].data();
			// 备份
			int weight = e[2];
			// 强制使用这条边
			cur = MST(i);
			if (cur > best)
			{
				// 什么都不是，删除它
				e[2] = -1;
				continue;
			}
			// 尝试删除
			e[2] = -1;
			cur = MST(-1);
			if (cur > best)
				R[0].push_back(e[3]);
			else
				R[1].push_back(e[3]);
			e[2] = weight;
		}
		return R;
	}
};


// 抄的
class Solution1
{
	typedef array<int, 3> Edge;
	vector<vector<int>> edges;
	// 用 vector<array<int, 100>> 很容易超时啊
	// to, cost, idx in edge
	vector<vector<array<int, 3>>> adj;
	vector<char> visit, valid;
	int n, len;

	// 练习使用 Prim 方法，不过太慢了
	// start 起始点，zero 0 边索引，block 删除边索引
	int MST(int start, int zero, int block)
	{
		int sum = 0, m = 0;
		visit.assign(n, 0);
		priority_queue<pair<int, int>> Q;
		// 一个虚拟的顶点，它到 start 的距离为 0
		Q.push({ 0, start });
		while (!Q.empty())
		{
			pair<int, int> q = Q.top();
			Q.pop();
			if (visit[q.second])
				continue;
			visit[q.second] = 1;
			sum -= q.first;
			if (++m == n)
				return sum;
			for (auto const& e : adj[q.second])
			{
				if (valid[e[2]] && (e[2] != block) && !(visit[e[0]]))
					Q.push({ (e[2] == zero ? 0 : -e[1]), e[0] });
			}
		}
		// 删除后可能根本不能生成树了
		// 这里主要是为了 n == 2 的情况，否则直接返回 INT_MAX
		return m == n ? sum : INT_MAX;
	}

public:
	vector<vector<int>> findCriticalAndPseudoCriticalEdges(int in_n,
		vector<vector<int>>& in_edges)
	{
		n = in_n;
		edges.swap(in_edges);
		len = static_cast<int>(edges.size());
		adj.resize(n);
		for (int i = 0; i < n; ++i)
			adj[i].clear();
		for (int i = 0; i < len; ++i)
		{
			// 人家要原来的索引
			edges[i].push_back(i);
			int* e = edges[i].data();
			adj[e[0]].push_back({ e[1], e[2], i });
			adj[e[1]].push_back({ e[0], e[2], i });
		}
		valid.assign(len, 1);
		sort(edges.begin(), edges.end(),
			[](vector<int> const& a, vector<int> const& b) -> bool
		{
			return a[2] < b[2];
		});

		vector<vector<int>> ans(2);
		int cur, best = MST(0, -1, -1);
		for (int i = 0; i < len; ++i)
		{
			int* e = edges[i].data();
			// 强制使用这条边
			cur = MST(e[0], e[3], -1) + e[2];
			// 加入这条边使得代价变大，则它不在任何 MST 里面
			if (cur > best)
			{
				// 删除，后面的 MST 不会把它往优先队列里面加
				valid[e[3]] = 0;
				continue;
			}
			// 尝试删除
			cur = MST(e[0], -1, e[3]);
			assert(cur >= best);
			// 删除后代价变大，说明是关键边
			if (cur > best)
				ans[0].push_back(e[3]);
			else
				ans[1].push_back(e[3]);
		}
		return ans;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 0, 1, 1 }, { 1, 2, 1 }, { 2, 3, 2 }, { 0, 3, 2 }, { 0, 4, 3 }, { 3, 4, 3 }, { 1, 4, 6 } },
		b = { { 0, 1, 1 }, { 1, 2, 1 }, { 2, 3, 1 }, { 0, 3, 1 } },
		c = { { 0, 1, 1 }, { 1, 2, 1 }, { 0, 2, 1 }, { 2, 3, 4 }, { 3, 4, 2 }, { 3, 5, 2 }, { 4, 5, 2 } },
		d = { { 0, 1, 3 } };
	Solution s;
	output(s.findCriticalAndPseudoCriticalEdges(5, a), "MST");
	output(s.findCriticalAndPseudoCriticalEdges(4, b), "MST");
	output(s.findCriticalAndPseudoCriticalEdges(6, c), "MST");
	output(s.findCriticalAndPseudoCriticalEdges(2, d), "MST");
}
