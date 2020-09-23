#include "leetcode.hpp"

/* 1553. 吃掉 N 个橘子的最少天数

厨房里总共有 n 个橘子，你决定每一天选择如下方式之一吃这些橘子：
	吃掉一个橘子。
	如果剩余橘子数 n 能被 2 整除，那么你可以吃掉 n/2 个橘子。
	如果剩余橘子数 n 能被 3 整除，那么你可以吃掉 2*(n/3) 个橘子。

每天你只能从以上 3 种方案中选择一种方案。

请你返回吃掉所有 n 个橘子的最少天数。

示例 1：
输入：n = 10
输出：4
解释：你总共有 10 个橘子。
第 1 天：吃 1 个橘子，剩余橘子数 10 - 1 = 9。
第 2 天：吃 6 个橘子，剩余橘子数 9 - 2*(9/3) = 9 - 6 = 3。（9 可以被 3 整除）
第 3 天：吃 2 个橘子，剩余橘子数 3 - 2*(3/3) = 3 - 2 = 1。
第 4 天：吃掉最后 1 个橘子，剩余橘子数 1 - 1 = 0。
你需要至少 4 天吃掉 10 个橘子。

示例 2：
输入：n = 6
输出：3
解释：你总共有 6 个橘子。
第 1 天：吃 3 个橘子，剩余橘子数 6 - 6/2 = 6 - 3 = 3。（6 可以被 2 整除）
第 2 天：吃 2 个橘子，剩余橘子数 3 - 2*(3/3) = 3 - 2 = 1。（3 可以被 3 整除）
第 3 天：吃掉剩余 1 个橘子，剩余橘子数 1 - 1 = 0。
你至少需要 3 天吃掉 6 个橘子。

示例 3：
输入：n = 1
输出：1

示例 4：
输入：n = 56
输出：6

提示：
	1 <= n <= 2*10^9
*/


class Solution1
{
public:
	int minDays(int n)
	{
		typedef pair<int, int> elem;
		unordered_map<int, int> M;
		priority_queue<elem> Q;
		M[n] = 0;
		Q.push({ 0, n });
		while (!Q.empty())
		{
			elem q = Q.top();
			Q.pop();
			auto it = M.find(q.second);
			if (q.first < it->second)
				continue;
			it->second = -(it->second);
			elem e(q.first - 1, q.second - 1);
			if (e.second == 0)
				return -(e.first);
			it = M.find(e.second);
			if (it == M.end() || e.first > it->second)
			{
				M[e.second] = e.first;
				Q.push(e);
			}
			e.second = q.second / 2;
			if (e.second * 2 == q.second)
			{
				if (e.second == 0)
					return -(e.first);
				it = M.find(e.second);
				if (it == M.end() || e.first > it->second)
				{
					M[e.second] = e.first;
					Q.push(e);
				}
			}
			e.second = q.second / 3;
			if (e.second * 3 == q.second)
			{
				if (e.second == 0)
					return -(e.first);
				it = M.find(e.second);
				if (it == M.end() || e.first > it->second)
				{
					M[e.second] = e.first;
					Q.push(e);
				}
			}
		}
		return 520;
	}
};


// https://leetcode-cn.com/problems/minimum-number-of-days-to-eat-n-oranges/solution/python3-8xing-dai-ma-shi-jian-fu-za-du-olog2ntu-ji/
// 抄的
class Solution
{
	unordered_map<int, int> M;

	int dfs(int n)
	{
		if (n <= 2)
			return n;
		int k = M[n];
		if (k > 0)
			return k;
		int a = n % 2 + dfs(n / 2);
		int b = n % 3 + dfs(n / 3);
		M[n] = k = min(a, b) + 1;
		return k;
	}

public:
	int minDays(int n)
	{
		return dfs(n);
	}
};


int main()
{
	Solution s;
	OutExpr(s.minDays(10), "%d");
	OutExpr(s.minDays(6), "%d");
	OutExpr(s.minDays(1), "%d");
	OutExpr(s.minDays(56), "%d");
}
