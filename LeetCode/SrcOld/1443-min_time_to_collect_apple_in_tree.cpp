#include "leetcode.hpp"

/* 1443. 收集树上所有苹果的最少时间

给你一棵有 n 个节点的无向树，节点编号为 0 到 n-1 ，它们中有一些节点有苹果。
通过树上的一条边，需要花费 1 秒钟。
你从 节点 0 出发，请你返回最少需要多少秒，可以收集到所有苹果，并回到节点 0 。

无向树的边由 edges 给出，其中 edges[i] = [fromi, toi] ，表示有一条边连接 from 和 toi 。
除此以外，还有一个布尔数组 hasApple ，其中 hasApple[i] = true 代表节点 i 有一个苹果，否则，节点 i 没有苹果。


示例 1：
https://assets.leetcode.com/uploads/2020/04/23/min_time_collect_apple_1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/10/min_time_collect_apple_1.png
输入：n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
输出：8
解释：上图展示了给定的树，其中红色节点表示有苹果。一个能收集到所有苹果的最优方案由绿色箭头表示。

示例 2：
https://assets.leetcode.com/uploads/2020/04/23/min_time_collect_apple_2.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/10/min_time_collect_apple_2.png
输入：n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,false,true,false]
输出：6
解释：上图展示了给定的树，其中红色节点表示有苹果。一个能收集到所有苹果的最优方案由绿色箭头表示。

示例 3：
输入：n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,false,false,false,false,false]
输出：0

提示：
	1 <= n <= 10^5
	edges.length == n-1
	edges[i].length == 2
	0 <= fromi, toi <= n-1
	fromi < toi
	hasApple.length == n
*/

// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/discuss/624095/3-solutions-simple-count-%2B-DFS-%2BBFS-%2B-picture-%2B-comments-%2B-road-metaphor
// 抄的，但是原答案现在过不去了
// LeetCode 加了用例，叶子节点的编号可能比父节点小，所以 BFS 吧
int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple)
{
	vector<vector<int>> adj(n);
	for (auto& e : edges)
	{
		adj[e[0]].push_back(e[1]);
		adj[e[1]].push_back(e[0]);
	}

	// 广搜，记录父节点、距离和访问顺序
	vector<int> par(n, n), dis(n, n), ord;
	vector<int> cur, tmp;
	cur.push_back(0);
	par[0] = dis[0] = 0;
	ord.push_back(0);
	for (int step = 1; !(cur.empty()); ++step)
	{
		tmp.clear();
		for (int f : cur)
			for (int t : adj[f])
			{
				if (par[t] < n)
					continue;
				par[t] = f;
				dis[t] = step;
				ord.push_back(t);
				tmp.push_back(t);
			}
		tmp.swap(cur);
	}

	// 统计苹果节点到最近访问过的父节点的距离
	int ans = 0;
	cur.assign(n, 0);
	cur[0] = 1;
	assert(static_cast<int>(dis.size()) == n);
	for (int i = n - 1; i >= 0; --i)
	{
		int t = ord[i];
		// 有苹果，还没有访问过
		if (hasApple[t] && !cur[t])
		{
			int f = t;
			while (!cur[f])
			{
				cur[f] = 1;
				f = par[f];
			}
			ans += 2 * (dis[t] - dis[f]);
		}
	}
	return ans;
}


int main()
{
	vector<vector<int>>
		A = { { 0, 1 }, { 0, 2 }, { 1, 4 }, { 1, 5 }, { 2, 3 }, { 2, 6 } },
		D = { { 0, 2 }, { 0, 3 }, { 1, 2 } };
	vector<bool>
		a = { false, false, true, false, true, true, false },
		b = { false, false, true, false, false, true, false },
		c = { false, false, false, false, false, false, false },
		d = { false, true, false, false };
	OutExpr(minTime(7, A, a), "%d");
	OutExpr(minTime(7, A, b), "%d");
	OutExpr(minTime(7, A, c), "%d");
	OutExpr(minTime(4, D, d), "%d");
}
