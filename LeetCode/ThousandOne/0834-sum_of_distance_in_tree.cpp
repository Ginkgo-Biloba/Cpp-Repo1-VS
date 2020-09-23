#include "leetcode.hpp"

/* 834. 树中距离之和

给定一个无向、连通的树。树中有 N 个标记为 0...N-1 的节点以及 N-1 条边。

第 i 条边连接节点 edges[i][0] 和 edges[i][1] 。

返回一个表示节点 i 与其他所有节点距离之和的列表 ans。

示例 1:

输入: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
输出: [8,12,6,10,10,10]
解释:
如下为给定的树的示意图：
	0
 / \
1   2
	 /|\
	3 4 5

我们可以计算出 dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
也就是 1 + 1 + 2 + 2 + 2 = 8。 因此，answer[0] = 8，以此类推。

说明: 1 <= N <= 10000
*/

// https://leetcode.com/problems/sum-of-distances-in-tree/discuss/130583/C%2B%2BJavaPython-Pre-order-and-Post-order-DFS-O(N)
// 抄的
class Solution
{
	int len;
	vector<vector<int>> adj;
	vector<int> dst, cnt;

	void dfs1(int root, int pre)
	{
		for (int i : adj[root])
		{
			if (i == pre)
				continue;
			dfs1(i, root);
			cnt[root] += cnt[i];
			dst[root] += dst[i] + cnt[i];
		}
	}

	void dfs2(int root, int pre)
	{
		for (int i : adj[root])
		{
			if (i == pre)
				continue;
			dst[i] = dst[root] + (len - cnt[i]) - cnt[i];
			dfs2(i, root);
		}
	}

public:
	vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges)
	{
		len = N;
		vector<int>(len, 0).swap(dst);
		vector<int>(len, 1).swap(cnt);
		adj.resize(len);
		for (int i = 0; i < N; ++i)
			adj.clear();
		for (auto const& e : edges)
		{
			adj[e[0]].push_back(e[1]);
			adj[e[1]].push_back(e[0]);
		}
		dfs1(0, -1);
		dfs2(0, -1);

		vector<int> d;
		d.swap(dst);
		return d;
	}
};


int main()
{
	vector<vector<int>>
		e0 = { { 0, 1 }, { 0, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 } };
	Solution s;
	output(s.sumOfDistancesInTree(6, e0), "Sum of Distances in Tree");
}
