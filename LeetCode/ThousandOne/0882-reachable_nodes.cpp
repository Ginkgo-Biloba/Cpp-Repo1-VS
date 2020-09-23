#include "leetcode.hpp"

/* 882. 细分图中的可到达结点

从具有 0 到 N-1 的结点的无向图（“原始图”）开始，对一些边进行细分。

该图给出如下：edges[k] 是整数对 (i, j, n) 组成的列表，使 (i, j) 是原始图的边。

n 是该边上新结点的总数

然后，将边 (i, j) 从原始图中删除，将 n 个新结点 (x_1, x_2, ..., x_n) 添加到原始图中，

将 n+1 条新边 (i, x_1), (x_1, x_2), (x_2, x_3), ..., (x_{n-1}, x_n), (x_n, j) 添加到原始图中。

现在，你将从原始图中的结点 0 处出发，并且每次移动，你都将沿着一条边行进。

返回最多 M 次移动可以达到的结点数。

示例 1：
输入：edges = [[0,1,10],[0,2,1],[1,2,2]], M = 6, N = 3
输出：13
解释：
在 M = 6 次移动之后在最终图中可到达的结点如下所示。

示例 2：
输入：edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], M = 10, N = 4
输出：23

提示：
	0 <= edges.length <= 10000
	0 <= edges[i][0] < edges[i][1] < N
	不存在任何 i != j 情况下 edges[i][0] == edges[j][0] 且 edges[i][1] == edges[j][1].
	原始图没有平行的边。
	0 <= edges[i][2] <= 10000
	0 <= M <= 10^9
	1 <= N <= 3000
	可到达结点是可以从结点 0 开始使用最多 M 次移动到达的结点。
*/

// https://leetcode-cn.com/problems/reachable-nodes-in-subdivided-graph/solution/xi-fen-tu-zhong-de-ke-dao-da-jie-dian-by-leetcode/
// 抄的，没看懂
int reachableNodes(vector<vector<int>>& edges, int M, int N)
{
	typedef pair<int, int> PII;
	vector<vector<PII>> adj(N);
	priority_queue<PII, vector<PII>, std::greater<PII>> q;
	std::map<int, int> dist;
	std::map<PII, int> used;
	int sum = 0;

	for (vector<int> const& e : edges)
	{
		adj[e[0]].emplace_back(e[1], e[2]);
		adj[e[1]].emplace_back(e[0], e[2]);
	}

	dist[0] = 0;
	for (int i = 1; i < N; ++i)
		dist[i] = M + 1;

	q.push({ 0, 0 });
	while (!q.empty())
	{
		auto cur = q.top();
		q.pop();
		int d = cur.first, node = cur.second;
		if (d > dist[node])
			continue;

		// 原始图中，每个点只到达一次
		++sum;

		for (auto const& e : adj[node])
		{
			int ngh = e.first;
			int wht = e.second;
			used[{ node, ngh }] = std::min(wht, M - d);

			int d2 = d + wht + 1;
			if (d2 < dist[ngh])
			{
				q.push({ d2, ngh });
				dist[ngh] = d2;
			}
		}
	}

	for (auto const& e : edges)
	{
		sum += std::min(e[2],
			used[{ e[0], e[1] }] + used[{ e[1], e[0] }]);
	}

	return sum;
}

int main()
{
	vector<vector<int>>
		a = { { 0, 1, 10 }, { 0, 2, 1 }, { 1, 2, 2 } },
		b = { { 0, 1, 4 }, { 1, 2, 6 }, { 0, 2, 8 }, { 1, 3, 1 } };
	OutExpr(reachableNodes(a, 6, 3), "%d");
	OutExpr(reachableNodes(b, 10, 4), "%d");
}
