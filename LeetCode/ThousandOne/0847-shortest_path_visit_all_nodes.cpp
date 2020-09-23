#include "leetcode.hpp"

/* 847. 访问所有节点的最短路径

给出 graph 为有 N 个节点（编号为 0, 1, 2, ..., N-1）的无向连通图。
graph.length = N，且只有节点 i 和 j 连通时，j != i 在列表 graph[i] 中恰好出现一次。
返回能够访问所有节点的最短路径的长度。
你可以在任一节点开始和停止，也可以多次重访节点，并且可以重用边。

示例 1：
输入：[[1,2,3],[0],[0],[0]]
输出：4
解释：一个可能的路径为 [1,0,2,0,3]

示例 2：
输入：[[1],[0,2,4],[1,3,4],[2],[1,2]]
输出：4
解释：一个可能的路径为 [0,1,4,2,3]

提示：
	1 <= graph.length <= 12
	0 <= graph[i].length < graph.length
*/

// https://leetcode-cn.com/problems/shortest-path-visiting-all-nodes/solution/fang-wen-suo-you-jie-dian-de-zui-duan-lu-jing-by-l/
// 抄的
int shortestPathLength(vector<vector<int>>& graph)
{
	int N = static_cast<int>(graph.size());
	vector<int> dist((1 << N) * N, N * N);
	auto at = [N](int y, int x) { return y * N + x; };
	vector<pair<int, int>> Q;
	int target = (1 << N) - 1;
	Q.reserve(1 << N);

	for (int x = 0; x < N; ++x)
	{
		Q.emplace_back(1 << x, x);
		dist[at(1 << x, x)] = 0;
	}

	for (size_t i = 0; i < Q.size(); ++i)
	{
		auto it = Q[i];
		int d1 = dist[at(it.first, it.second)] + 1;
		for (int child : graph[it.second])
		{
			int visit = (it.first) | (1 << child);
			if (visit == target)
				return d1;
			if (d1 < dist[at(visit, child)])
			{
				dist[at(visit, child)] = d1;
				Q.emplace_back(visit, child);
			}
		}
	}

	return dist.back();
}


int main()
{
	vector<vector<int>>
		a = { { 1, 2, 3 }, { 0 }, { 0 }, { 0 } },
		b = { { 1 }, { 0, 2, 4 }, { 1, 3, 4 }, { 2 }, { 1, 2 } };
	OutExpr(shortestPathLength(a), "%d");
	OutExpr(shortestPathLength(b), "%d");
}
