#include "leetcode.hpp"

/* 310. 最小高度树

对于一个具有树特征的无向图，我们可选择任何一个节点作为根。
图因此可以成为树，在所有可能的树中，具有最小高度的树被称为最小高度树。
给出这样的一个图，写出一个函数找到所有的最小高度树并返回他们的根节点。

格式

该图包含 n 个节点，标记为 0 到 n - 1。
给定数字 n 和一个无向边 edges 列表（每一个边都是一对标签）。

你可以假设没有重复的边会出现在 edges 中。由于所有的边都是无向边， [0, 1]和 [1, 0] 是相同的，因此不会同时出现在 edges 里。

示例 1:
输入: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

>        0
>        |
>        1
>       / \
>      2   3

输出: [1]

示例 2:
输入: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

>     0  1  2
>      \ | /
>        3
>        |
>        4
>        |
>        5

输出: [3, 4]

说明:
	根据树的定义，树是一个无向图，其中任何两个顶点只通过一条路径连接。
	换句话说，一个任何没有简单环路的连通图都是一棵树。
	树的高度是指根节点和叶子节点之间最长向下路径上边的数量。
*/

class Solution
{
	vector<int> par, dis, pre, cur;
	vector<vector<int>> adj;
	int num, hmax, imax;

	void bfs(int start)
	{
		hmax = imax = 0;
		cur.push_back(start);
		par[start] = start;
		dis.assign(num, -1);
		dis[start] = 0;
		while (cur.size())
		{
			pre.swap(cur);
			cur.clear();
			for (int p : pre)
				for (int k : adj[p])
				{
					if (dis[k] >= 0)
						continue;
					hmax = dis[k] = dis[p] + 1;
					par[k] = p;
					imax = k;
					cur.push_back(k);
				}
		}
	}

public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges)
	{
		vector<int> ans;
		if (n <= 0) return ans;
		if (n == 1)
		{
			ans.push_back(0);
			return ans;
		}
		num = n;
		par.resize(n);
		adj.resize(n);
		for (int i = 0; i < n; ++i)
			adj[i].clear();
		for (auto& e : edges)
		{
			adj[e[0]].push_back(e[1]);
			adj[e[1]].push_back(e[0]);
		}

		bfs(0);
		bfs(imax);
		for (int h = (hmax / 2); h > 0; --h)
			imax = par[imax];
		ans.push_back(imax);
		if (hmax & 1)
			ans.push_back(par[imax]);
		return ans;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 1, 0 }, { 1, 2 }, { 1, 3 } },
		b = { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 4, 3 }, { 5, 4 } };
	Solution s;
	output(s.findMinHeightTrees(4, a), "Minimum Height Trees");
	output(s.findMinHeightTrees(6, b), "Minimum Height Trees");
}
