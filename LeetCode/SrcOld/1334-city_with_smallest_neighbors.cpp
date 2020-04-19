#include "leetcode.hpp"

/* 1334. 阈值距离内邻居最少的城市

有 n 个城市，按从 0 到 n-1 编号。给你一个边数组 edges，其中 edges[i] = [fromi, toi, weighti] 代表 fromi 和 toi 两个城市之间的双向加权边，距离阈值是一个整数 distanceThreshold。

返回能通过某些路径到达其他城市数目最少、且路径距离 最大 为 distanceThreshold 的城市。
如果有多个这样的城市，则返回编号最大的城市。

注意，连接城市 i 和 j 的路径的距离等于沿该路径的所有边的权重之和。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/26/find_the_city_01.png
输入：n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
输出：3
解释：城市分布图如上。
每个城市阈值距离 distanceThreshold = 4 内的邻居城市分别是：
城市 0 -> [城市 1, 城市 2]
城市 1 -> [城市 0, 城市 2, 城市 3]
城市 2 -> [城市 0, 城市 1, 城市 3]
城市 3 -> [城市 1, 城市 2]
城市 0 和 3 在阈值距离 4 以内都有 2 个邻居城市，但是我们必须返回城市 3，因为它的编号最大。

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/26/find_the_city_02.png
输入：n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
输出：0
解释：城市分布图如上。
每个城市阈值距离 distanceThreshold = 2 内的邻居城市分别是：
城市 0 -> [城市 1]
城市 1 -> [城市 0, 城市 4]
城市 2 -> [城市 3, 城市 4]
城市 3 -> [城市 2, 城市 4]
城市 4 -> [城市 1, 城市 2, 城市 3]
城市 0 在阈值距离 4 以内只有 1 个邻居城市。

提示：
	2 <= n <= 100
	1 <= edges.length <= n * (n - 1) / 2
	edges[i].length == 3
	0 <= fromi < toi < n
	1 <= weighti, distanceThreshold <= 10^4
	所有 (fromi, toi) 都是不同的。
*/

class Solution_1
{
	int adj[100][100];
	priority_queue<pair<int, int>> Q;
	int dist[100];
	char visit[100];

	int Dijkstra(int n, int start, int T)
	{
		memset(visit, 0, sizeof(visit));
		memset(dist, 0x3f, sizeof(dist));
		dist[start] = 0;
		Q.emplace(0, start);
		while (!Q.empty())
		{
			int d = -Q.top().first, i = Q.top().second;
			Q.pop();
			if (visit[i])
				continue;
			visit[i] = 1;
			for (int k = 0; k < n; ++k)
				if (adj[i][k])
				{
					int kd = d + adj[i][k];
					if (kd < dist[k] && kd <= T)
					{
						dist[k] = kd;
						Q.emplace(-kd, k);
					}
				}
		}

		int cur = 0;
		for (int i = 0; i < n; ++i)
		{
			if (dist[i] < 0x3f3f3f3f)
				++cur;
		}
		return cur;
	}

public:
	int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
	{
		memset(adj, 0, sizeof(adj));
		for (auto const& e : edges)
		{
			adj[e[0]][e[1]] = e[2];
			adj[e[1]][e[0]] = e[2];
		}
		int k = -1, d = INT_MAX, cur = 0;
		for (int i = 0; i < n; ++i)
		{
			cur = Dijkstra(n, i, distanceThreshold);
			if (cur <= d)
			{
				d = cur;
				k = i;
			}
		}
		return k;
	}
};

// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/discuss/490312/JavaC%2B%2BPython-Easy-Floyd-Algorithm
// 抄的
class Solution
{
	vector<int> adj, dis;
	int len;

	int at(int y, int x)
	{
		return y * len + x;
	}

public:
	int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
	{
		len = n;
		dis.assign(n * n, INT_MAX / 4);
		for (auto const& e : edges)
		{
			dis[at(e[0], e[1])] = e[2];
			dis[at(e[1], e[0])] = e[2];
		}
		for (int i = 0; i < n; ++i)
			dis[at(i, i)] = 0;

		for (int i = 0; i < n; ++i)
		{
			for (int h = 0; h < n; ++h)
				for (int k = 0; k < n; ++k)
				{
					dis[at(h, k)] = min(dis[at(h, k)],
						dis[at(h, i)] + dis[at(i, k)]);
				}
		}

		int num = n, idx = -1;
		for (int i = 0; i < n; ++i)
		{
			int cur = 0;
			for (int k = 0; k < n; ++k)
				cur += (dis[at(i, k)] <= distanceThreshold);
			if (cur <= num)
			{
				num = cur;
				idx = i;
			}
		}
		return idx;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 0, 1, 3 }, { 1, 2, 1 }, { 1, 3, 4 }, { 2, 3, 1 } },
		b = { { 0, 1, 2 }, { 0, 4, 8 }, { 1, 2, 3 }, { 1, 4, 2 }, { 2, 3, 1 }, { 3, 4, 1 } };
	Solution s;
	OutExpr(s.findTheCity(4, a, 4), "%d");
	OutExpr(s.findTheCity(5, b, 2), "%d");
}
