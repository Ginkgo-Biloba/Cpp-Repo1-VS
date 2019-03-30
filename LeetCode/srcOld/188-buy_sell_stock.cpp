#include <vector>
#include <cstdio>
#include <algorithm>

// 123. 最多交易 2 次。用状态机 (动态规划) 更好
int maxProfit2(std::vector<int>& prices)
{
	int const len = static_cast<int>(prices.size());
	if (len < 2u) return 0;
	std::vector<int> forward(len), backward(len);
	int minf = prices[0], maxb = prices[len - 1u];

	int ans = 0;
	for (size_t i = 1; i < len; i++)
	{
		if (prices[i] > minf)
		{
			int const cur = (prices[i] - minf);
			if (ans < cur) ans = cur;
		}
		else
			minf = prices[i];

		forward[i] = ans;
	}
	ans = 0;
	for (size_t i = len - 2u; i != (size_t)(-1); i--)
	{
		if (prices[i] < maxb)
		{
			int const cur = (maxb - prices[i]);
			if (ans < cur) ans = cur;
		}
		else
			maxb = prices[i];

		backward[i] = ans;
	}
	ans = backward[0];
	for (size_t i = 1; i < len; i++)
	{
		int const cur = forward[i - 1u] + backward[i];
		if (ans < cur) ans = cur;
	}

	return ans;
}


// 188. 最多交易 k 次，使用状态机，参考 2 次交易的讨论
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/149383/Easy-DP-solution-using-state-machine-O(n)-time-complexity-O(1)-space-complexity
int maxProfitK(int k, std::vector<int>& prices)
{
	int const len = static_cast<int>(prices.size());
	if ((len < 2) || (k < 1)) return 0;
	k = std::min<int>(k, len / 2);

	int const kk = static_cast<int>(k + k);
	std::vector<int> states(kk, INT_MIN);
	states[0] = -prices[0];

	for (int idx = 1; idx < len; idx++)
	{
		int const p = prices[idx];
		states[0] = std::max(states[0], -p);
		states[1] = std::max(states[1], states[0] + p);
		for (int i = 2; i < kk; i += 2)
		{
			states[i] = std::max(states[i], states[i - 1] - p);
			states[i + 1] = std::max(states[i + 1], states[i] + p);
		}
	}

	int ans = states.back();
	if (ans < 0) ans = 0;  // 1 次都不交易
	return ans;
}


// 309. 卖出的下一天不能买
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75930/Very-Easy-to-Understand-One-Pass-O(n)-Solution-with-No-Extra-Space
int maxProfitCD(std::vector<int>& prices)
{
	int const len = static_cast<int>(prices.size());
	if (len < 2) return 0;

	int sell = INT_MIN;   // 有股票，卖掉     1 <- (2, 3)
	int hold = INT_MIN;   // 有股票，不操作   2 <- (2, 3)
	int buy = -prices[0]; // 没有股票，买进   3 <- (4)
	int cool = 0;         // 没有股票，不操作 4 <- (1, 4)

	for (int i = 0; i < len; i++)
	{
		int const p = prices[i];

		// 根据依赖关系得到更新顺序 2, 3, 4, 1
		// 一步步计算会发现不需要 newsell
		// int const newsell = std::max(hold, buy) + p; 
		hold = std::max(hold, buy);
		buy = cool - p;
		cool = std::max(sell, cool);
		sell = hold + p; // newsell
	}

	int ans = std::max(sell, cool);
	return ans;
}


// 714. 任意多次，交易一次有费用。参考 2 次的讨论
int maxProfitTF(std::vector<int>& prices, int fee)
{
	int const len = static_cast<int>(prices.size());
	if (len < 2) return 0;

	int sell = INT_MIN / 2; // 有股票，卖掉     1 <- (2, 3)
	int hold = INT_MIN / 2; // 有股票，不操作   2 <- (2, 3)
	int buy = -prices[0];   // 没有股票，买进   3 <- (4)
	int cool = 0;           // 没有股票，不操作 4 <- (1, 4)

	for (int i = 1; i < len; i++)
	{
		int const p = prices[i];
		hold = std::max(hold, buy);
		cool = std::max(sell, cool);
		buy = cool - p; // 因为无限次交易，所以可以用新的 cool 表示卖了立即买
		sell = hold + p - fee;
	}

	int ans = std::max(sell, cool);
	return ans;
}


int main()
{
	std::vector<int> prices = { 1, 2, 3, 0, 2 };
	int ans = 0;
	ans = maxProfit2(prices);
	ans = maxProfitK(2, prices);
	ans = maxProfitCD(prices);
	printf("ans = %d\n", ans);
	return 0;
}

