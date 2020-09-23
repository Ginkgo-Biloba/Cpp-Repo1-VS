#include "leetcode.hpp"

/* 123. 买卖股票的最佳时机 III

给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:
输入: [3,3,5,0,0,3,1,4]
输出: 6
解释:
在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。

示例 2:
输入: [1,2,3,4,5]
输出: 4
解释:
在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

示例 3:
输入: [7,6,4,3,1]
输出: 0
解释: 在这个情况下, 没有交易完成, 所以最大利润为 0。
*/


int maxProfit(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	if (len < 2)
		return 0;
	int b0 = -A[0], s0 = 0, b1 = INT_MIN, s1 = 0;
	for (int i = 1; i < len; ++i)
	{
		// s0 -> s1 in 1 day 
		// because we can sell and then buy and then sell again
		s0 = max(s0, b0 + A[i]);
		b1 = max(b1, s0 - A[i]);
		s1 = max(s1, b1 + A[i]);
		b0 = max(b0, -A[i]);
	}
	return s1;
}


int main()
{
	vector<int>
		a = { 3, 3, 5, 0, 0, 3, 1, 4 },
		b = { 1, 2, 3, 4, 5 },
		c = { 7, 6, 4, 3, 1 },
		d = { 2, 1, 4, 5, 2, 9, 7 };
	OutExpr(maxProfit(d), "%d");
	OutExpr(maxProfit(a), "%d");
	OutExpr(maxProfit(b), "%d");
	OutExpr(maxProfit(c), "%d");
}
