#include "leetcode.hpp"

/* 1584. 连接所有点的最小费用

给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。

连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。

请你返回将所有点连接的最小总费用。
只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。

示例 1：
https://assets.leetcode.com/uploads/2020/08/26/d.png
输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
输出：20
解释：
https://assets.leetcode.com/uploads/2020/08/26/c.png
我们可以按照上图所示连接所有点得到最小总费用，总费用为 20 。
注意到任意两个点之间只有唯一一条路径互相到达。

示例 2：
输入：points = [[3,12],[-2,5],[-4,1]]
输出：18

示例 3：
输入：points = [[0,0],[1,1],[1,0],[-1,1]]
输出：4

示例 4：
输入：points = [[-1000000,-1000000],[1000000,1000000]]
输出：4000000

示例 5：
输入：points = [[0,0]]
输出：0

提示：
	1 <= points.length <= 1000
	-106 <= xi, yi <= 106
	所有点 (xi, yi) 两两不同。
*/


int minCostConnectPoints1(vector<vector<int>>& points)
{
	int n = static_cast<int>(points.size());
	vector<array<int, 1000>> dis(n);
	vector<char> vis(n);
	memset(dis.data(), 0xff, n * sizeof(dis[0]));
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			int x = points[i][0] - points[j][0];
			int y = points[i][1] - points[j][1];
			int d = abs(x) + abs(y);
			dis[i][j] = dis[j][i] = d;
		}

	int ans = 0, num = 0;
	priority_queue<pair<int, int>> Q;
	Q.push({ 0, 0 });
	while (Q.size())
	{
		int d = Q.top().first;
		int i = Q.top().second;
		Q.pop();
		if (vis[i])
			continue;
		ans -= d;
		vis[i] = 1;
		num += 1;
		if (num == n)
			break;
		for (int j = 0; j < n; ++j)
		{
			d = dis[i][j];
			if (vis[j] || d < 0)
				continue;
			dis[i][j] = dis[j][i] = -1;
			Q.push({ -d, j });
		}
	}
	return ans;
}


// 抄的 cuiaoxiang 的，竟然是 O(N^2) 的
int minCostConnectPoints(vector<vector<int>>& points)
{
	int len = static_cast<int>(points.size());
	int road = 0;
	vector<int> dist(len, INT_MAX);
	vector<char> join(len, 0);
	dist[0] = 0;
	for (int i = 0; i < len; ++i)
	{
		int nearest = INT_MAX;
		int newcity = -1;
		for (int k = 0; k < len; ++k)
			if (!join[k] && (dist[k] < nearest))
			{
				nearest = dist[k];
				newcity = k;
			}
		road += nearest;
		join[newcity] = 1;
		for (int k = 0; k < len; ++k)
			if (!join[k])
			{
				int x = points[newcity][0] - points[k][0];
				int y = points[newcity][1] - points[k][1];
				int d = abs(x) + abs(y);
				dist[k] = min(dist[k], d);
			}
	}
	return road;
}


int main()
{
	vector<vector<int>>
		a = { { 0, 0 }, { 2, 2 }, { 3, 10 }, { 5, 2 }, { 7, 0 } },
		b = { { 3, 12 }, { -2, 5 }, { -4, 1 } },
		c = { { 0, 0 }, { 1, 1 }, { 1, 0 }, { -1, 1 } },
		d = { { -1000000, -1000000 }, { 1000000, 1000000 } },
		e = { { 0, 0 } };
	OutExpr(minCostConnectPoints(a), "%d");
	OutExpr(minCostConnectPoints(b), "%d");
	OutExpr(minCostConnectPoints(c), "%d");
	OutExpr(minCostConnectPoints(d), "%d");
	OutExpr(minCostConnectPoints(e), "%d");
}
