#include "leetcode.hpp"

/* 743. 网络延迟时间

有 N 个网络节点，标记为 1 到 N。

给定一个列表 times，表示信号经过有向边的传递时间。
times[i] = (u, v, w)，其中 u 是源节点，v 是目标节点，w 是一个信号从源节点传递到目标节点的时间。

现在，我们向当前的节点 K 发送了一个信号。
需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1。

注意:
	N 的范围在 [1, 100] 之间。
	K 的范围在 [1, N] 之间。
	times 的长度在 [1, 6000] 之间。
	所有的边 times[i] = (u, v, w) 都有 1 <= u, v <= N 且 0 <= w <= 100。
*/

// Djikstra

struct elem
{
	int d, n;
	bool operator <(elem const& e) const
	{
		return (d > e.d) || (d == e.d && n > e.n);
	}
};

int networkDelayTime(vector<vector<int>>& times, int N, int K)
{
	vector<int> adj(N * N, -1);
	vector<int> dst(N, INT_MAX);
	priority_queue<elem> pq;

	for (vector<int> const& t : times)
		adj[(t[0] - 1) * N + (t[1] - 1)] = t[2];

	pq.push({ 0, K - 1 });
	while (!pq.empty())
	{
		elem e = pq.top();
		pq.pop();
		if (dst[e.n] < e.d)
			continue;
		dst[e.n] = e.d;
		int* A = adj.data() + e.n * N;
		for (int i = 0; i < N; ++i)
		{
			if (A[i] < 0)
				continue;
			int id = A[i] + e.d;
			if (id < dst[i])
			{
				dst[i] = id;
				pq.push({ id, i });
			}
		}
	}

	K = 0;
	for (int i = 0; i < N; ++i)
	{
		if (dst[i] == INT_MAX)
			return -1;
		K = std::max(K, dst[i]);
	}
	return K;
}


int main()
{
	vector<vector<int>> grid = {
		{ 1, 2, 1 },
		{ 2, 3, 2 },
		{ 1, 3, 4 },
	};
	OutExpr(networkDelayTime(grid, 3, 1), "%d");
}
