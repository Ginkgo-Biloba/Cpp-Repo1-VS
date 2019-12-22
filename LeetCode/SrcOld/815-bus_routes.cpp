#include "leetcode.hpp"

/* 815. 公交路线

我们有一系列公交路线。每一条路线 routes[i] 上都有一辆公交车在上面循环行驶。
例如，有一条路线 routes[0] = [1, 5, 7]，表示第一辆 (下标为0) 公交车会一直按照 1->5->7->1->5->7->1->... 的车站路线行驶。

假设我们从 S 车站开始（初始时不在公交车上），要去往 T 站。
期间仅可乘坐公交车，求出最少乘坐的公交车数量。返回 -1 表示不可能到达终点车站。

示例:
输入:
routes = [[1, 2, 7], [3, 6, 7]]
S = 1
T = 6
输出: 2
解释:
最优策略是先乘坐第一辆公交车到达车站 7, 然后换乘第二辆公交车到车站 6。

说明:
	1 <= routes.length <= 500.
	1 <= routes[i].length <= 500.
	0 <= routes[i][j] < 10 ^ 6.
*/

// https://leetcode.com/problems/bus-routes/discuss/122771/C%2B%2BJavaPython-BFS-Solution
int numBusesToDestination(vector<vector<int>>& routes, int S, int T)
{
	unordered_map<int, vector<int>> to_routes;
	int len = static_cast<int>(routes.size());
	for (int i = 0; i < len; ++i)
		for (int j : routes[i])
			to_routes[j].push_back(i);
	std::queue<pair<int, int>> bfs;
	bfs.push({ S, 0 });
	unordered_set<int> seen = { S };
	while (!bfs.empty())
	{
		int stop = bfs.front().first, bus = bfs.front().second;
		bfs.pop();
		if (stop == T)
			return bus;
		for (int i : to_routes[stop])
		{
			for (int j : routes[i])
			{
				if (seen.find(j) == seen.end())
				{
					seen.insert(j);
					bfs.push({ j, bus + 1 });
				}
			}
			// 这个可以去掉回头路
			routes[i].clear();
		}
	}
	return -1;
}


int main()
{
	vector<vector<int>>
		r0 = { { 1, 2, 7 }, { 3, 6, 7 } };
	OutExpr(numBusesToDestination(r0, 1, 6), "%d");
}
