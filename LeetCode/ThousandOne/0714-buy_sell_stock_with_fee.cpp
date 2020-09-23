#include "leetcode.hpp"

/* 714. 买卖股票的最佳时机含手续费

给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格；非负整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每次交易都需要付手续费。
如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

示例 1:
输入: prices = [1, 3, 2, 8, 4, 9], fee = 2
输出: 8
解释: 能够达到的最大利润:
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

注意:
	0 < prices.length <= 50000.
	0 < prices[i] < 50000.
	0 <= fee < 50000.
*/

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108867/C%2B%2B-concise-solution-O(n)-time-O(1)-space
// 抄的
int maxProfit(vector<int>& prices, int fee)
{
	// s0 手上没有 s1 手上有
	int s0 = 0, s1 = -50000;
	for (int p : prices)
	{
		s0 = std::max(s0, s1 + p - fee);
		s1 = std::max(s1, s0 - p);
	}
	return s0;
}


int main()
{
	vector<int> p1 = { 1, 3, 2, 8, 4, 9 };
	OutExpr(maxProfit(p1, 2), "%d");
}
