#include "leetcode.hpp"

/* 1786. 从第一个节点出发到最后一个节点的受限路径数

现有一个加权无向连通图。
给你一个正整数 n ，表示图中有 n 个节点，并按从 1 到 n 给节点编号；另给你一个数组 edges ，其中每个 edges[i] = [ui, vi, weighti] 表示存在一条位于节点 ui 和 vi 之间的边，这条边的权重为 weighti 。

从节点 start 出发到节点 end 的路径是一个形如 [z0, z1, z2, ..., zk] 的节点序列，满足 z0 = start 、zk = end 且在所有符合 0 <= i <= k-1 的节点 zi 和 zi+1 之间存在一条边。

路径的距离定义为这条路径上所有边的权重总和。
用 distanceToLastNode(x) 表示节点 n 和 x 之间路径的最短距离。
受限路径 为满足 distanceToLastNode(zi) > distanceToLastNode(zi+1) 的一条路径，其中 0 <= i <= k-1 。

返回从节点 1 出发到节点 n 的 受限路径数 。
由于数字可能很大，请返回对 10^9 + 7 取余 的结果。

示例 1：
https://assets.leetcode.com/uploads/2021/02/17/restricted_paths_ex1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/03/07/restricted_paths_ex1.png
输入：n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
输出：3
解释：每个圆包含黑色的节点编号和蓝色的 distanceToLastNode 值。
三条受限路径分别是：
1) 1 --> 2 --> 5
2) 1 --> 2 --> 3 --> 5
3) 1 --> 3 --> 5

示例 2：
https://assets.leetcode.com/uploads/2021/02/17/restricted_paths_ex22.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/03/07/restricted_paths_ex22.png
输入：n = 7, edges = [[1,3,1],[4,1,2],[7,3,4],[2,5,3],[5,6,1],[6,7,2],[7,5,3],[2,6,4]]
输出：1
解释：每个圆包含黑色的节点编号和蓝色的 distanceToLastNode 值。
唯一一条受限路径是：1 --> 3 --> 7 。

提示：
	1 <= n <= 2 * 10^4
	n - 1 <= edges.length <= 4 * 10^4
	edges[i].length == 3
	1 <= ui, vi <= n
	ui != vi
	1 <= weighti <= 10^5
	任意两个节点之间至多存在一条边
	任意两个节点之间至少存在一条路径
*/

// https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/discuss/1097478/C%2B%2B-Dijkstra-%2B-DP
// 抄的
int countRestrictedPaths(int n, vector<vector<int>>& edges)
{
	using pii = pair<int, int>;
	int const mod = static_cast<int>(1e9 + 7);
	vector<int> dst(n, INT_MAX);
	vector<int> ans(n);
	vector<vector<array<int, 2>>> adj(n);
	for (auto const& e : edges)
	{
		adj[e[0] - 1].push_back({ e[1] - 1, e[2] });
		adj[e[1] - 1].push_back({ e[0] - 1, e[2] });
	}
	priority_queue<pii, vector<pii>, std::greater<pii>> q;
	dst[n - 1] = 0;
	ans[n - 1] = 1;
	q.push({ 0, n - 1 });
	while (q.size())
	{
		int d = q.top().first;
		int i = q.top().second;
		q.pop();
		if (d > dst[i])
			continue;
		for (auto const& ngh : adj[i])
		{
			int k = ngh[0];
			int e = ngh[1] + d;
			if (e < dst[k])
			{
				dst[k] = e;
				q.push({ e, k });
			}
			if (d > dst[k])
				ans[i] = (ans[i] + ans[k]) % mod;
		}
	}
	return ans[0];
}


int main()
{}
