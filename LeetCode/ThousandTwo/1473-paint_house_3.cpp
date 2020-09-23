#include "leetcode.hpp"

/* 1473. 给房子涂色 III

在一个小城市里，有 m 个房子排成一排，你需要给每个房子涂上 n 种颜色之一（颜色编号为 1 到 n ）。
有的房子去年夏天已经涂过颜色了，所以这些房子不需要被重新涂色。

我们将连续相同颜色尽可能多的房子称为一个街区。
比方说 houses = [1,2,2,3,3,2,1,1] ，它包含 5 个街区  [{1}, {2,2}, {3,3}, {2}, {1,1}] 。

给你一个数组 houses ，一个 m * n 的矩阵 cost 和一个整数 target ，其中：
	houses[i]：是第 i 个房子的颜色，0 表示这个房子还没有被涂色。
	cost[i][j]：是将第 i 个房子涂成颜色 j+1 的花费。

请你返回房子涂色方案的最小总花费，使得每个房子都被涂色后，恰好组成 target 个街区。
如果没有可用的涂色方案，请返回 -1 。

示例 1：
输入：
houses = [0,0,0,0,0],
cost = [[1,10],[10,1],[10,1],[1,10],[5,1]],
m = 5, n = 2, target = 3
输出：9
解释：房子涂色方案为 [1,2,2,1,1]
此方案包含 target = 3 个街区，分别是 [{1}, {2,2}, {1,1}]。
涂色的总花费为 (1 + 1 + 1 + 1 + 5) = 9。

示例 2：
输入：
houses = [0,2,1,2,0],
cost = [[1,10],[10,1],[10,1],[1,10],[5,1]],
m = 5, n = 2, target = 3
输出：11
解释：有的房子已经被涂色了，在此基础上涂色方案为 [2,2,1,2,2]
此方案包含 target = 3 个街区，分别是 [{2,2}, {1}, {2,2}]。
给第一个和最后一个房子涂色的花费为 (10 + 1) = 11。

示例 3：
输入：
houses = [0,0,0,0,0],
cost = [[1,10],[10,1],[1,10],[10,1],[1,10]],
m = 5, n = 2, target = 5
输出：5

示例 4：

输入：
houses = [3,1,2,3],
cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]],
m = 4, n = 3, target = 3
输出：-1
解释：房子已经被涂色并组成了 4 个街区，分别是 [{3},{1},{2},{3}] ，无法形成 target = 3 个街区。

提示：
	m == houses.length == cost.length
	n == cost[i].length
	1 <= m <= 100
	1 <= n <= 20
	1 <= target <= m
	0 <= houses[i] <= n
	1 <= cost[i][j] <= 10^4
*/

// https://leetcode.com/problems/paint-house-iii/discuss/674313/Simple-Python-explanation-and-why-I-prefer-top-down-DP-to-bottom-up
// 抄的
class Solution
{
	enum { inf = static_cast<int>(1e9 + 7) };

	int buffer[101][21][101];
	int m, n;
	vector<int> houses;
	vector<vector<int>> cost;

	// 将房子 (i - 1) 染色成 p 并且房子 [i, m) 有 t 个街区的最小代价
	int dp(int i, int p, int t)
	{
		if ((i == m) || (t < 0) || (m - i < t))
		{
			if ((i == m) && (t == 0))
				return 0;
			else
				return inf;
		}

		int k = i + 1;
		int val = buffer[i][p][t];
		if (val > 0)
			return val;

		val = inf;
		if (houses[i] == 0)
			for (int q = 1; q <= n; ++q)
			{
				int u = t - (q != p);
				u = dp(k, q, u) + cost[i][q - 1];
				val = min(val, u);
			}
		else
		{
			int u = t - (houses[i] != p);
			val = dp(k, houses[i], u);
		}
		return (buffer[i][p][t] = val);
	}

public:
	int minCost(vector<int>& _houses,
		vector<vector<int>>& _cost, int _m, int _n, int target)
	{
		houses.swap(_houses);
		cost.swap(_cost);
		m = _m;
		n = _n;
		memset(buffer, 0, sizeof(buffer));
		int val = dp(0, 0, target);
		return (val == inf) ? -1 : val;
	}
};


int main()
{
	vector<int>
		a = { 0, 0, 0, 0, 0 },
		b = { 0, 2, 1, 2, 0 },
		c = { 0, 0, 0, 0, 0 },
		d = { 3, 1, 2, 3 };
	vector<vector<int>>
		h = { { 1, 10 }, { 10, 1 }, { 10, 1 }, { 1, 10 }, { 5, 1 } },
		i = h,
		j = { { 1, 10 }, { 10, 1 }, { 1, 10 }, { 10, 1 }, { 1, 10 } },
		k = { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } };
	Solution s;
	OutExpr(s.minCost(a, h, 5, 2, 3), "%d");
	OutExpr(s.minCost(b, i, 5, 2, 3), "%d");
	OutExpr(s.minCost(c, j, 5, 2, 5), "%d");
	OutExpr(s.minCost(d, k, 4, 3, 3), "%d");
}
