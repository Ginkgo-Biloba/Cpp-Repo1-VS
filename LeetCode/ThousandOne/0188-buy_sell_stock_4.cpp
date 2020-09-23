#include "leetcode.hpp"

/* 188. 买卖股票的最佳时机 IV

给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:
输入: [2,4,1], k = 2
输出: 2
解释:
在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。

示例 2:
输入: [3,2,6,5,0,3], k = 2
输出: 7
解释:
在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
*/

int maxProfit_Org(int k, vector<int>& prices)
{
	int len = static_cast<int>(prices.size());
	if (len < 1 || k < 1)
		return 0;
	if (k * 2 >= len)
	{
		int sum = 0;
		for (int i = 1; i < len; ++i)
			sum += max(prices[i] - prices[i - 1], 0);
		return sum;
	}
	vector<int> buy(k, INT_MIN), sel(k);
	for (int i = 0; i < len; ++i)
	{
		int cur = prices[i];
		buy[0] = max(buy[0], -cur);
		sel[0] = max(sel[0], buy[0] + cur);
		for (int n = 1; n < k; ++n)
		{
			buy[n] = max(buy[n], sel[n - 1] - cur);
			sel[n] = max(sel[n], buy[n] + cur);
		}
	}
	return sel[k - 1];
}


// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/54118/C%2B%2B-Solution-with-O(n-%2B-klgn)-time-using-Max-Heap-and-Stack
// 抄的
int maxProfit(int ktime, vector<int>& prices)
{
	int len = static_cast<int>(prices.size());
	vector<pair<int, int>> s;
	priority_queue<int> d;

	for (int i = 0; i < len;)
	{
		int v = i, k = i + 1;
		while (k < len && prices[k - 1] <= prices[k])
			++k;
		if (k == i + 1)
		{
			i = k;
			continue;
		}
		// [i...k) 非递减
		while (!s.empty()
			&& prices[v] < prices[s.back().first])
		{
			d.push(prices[s.back().second - 1] - prices[s.back().first]);
			s.pop_back();
		}
		while (!s.empty()
			&& prices[k - 1] >= prices[s.back().second - 1])
		{
			d.push(prices[s.back().second - 1] - prices[v]);
			v = s.back().first;
			s.pop_back();
		}
		s.push_back({ v, k });
		i = k;
	}
	while (!s.empty())
	{
		d.push(prices[s.back().second - 1] - prices[s.back().first]);
		s.pop_back();
	}

	int ans = 0;
	ktime = min(ktime, static_cast<int>(d.size()));
	for (; ktime > 0; --ktime)
	{
		ans += d.top();
		d.pop();
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 2, 4, 1 },
		b = { 3, 2, 6, 5, 0, 3 },
		c = { 1, 2, 4, 2, 5, 7, 2, 4, 9, 0 };
	OutExpr(maxProfit(2, a), "%d");
	OutExpr(maxProfit(2, b), "%d");
	OutExpr(maxProfit(4, c), "%d");
}
