#include "../srcOld/utility.hpp"

/* 322. 零钱兑换
 * 给定不同面额的硬币 coins 和一个总金额 amount。
 * 编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
 * 如果没有任何一种硬币组合能组成总金额，返回 -1。
 */

 // 看相关话题知道是动态规划，但是还是要写成广搜加上剪枝
 // 虽说不会 amount 是 INT_MAX 的时候 coins 只有 1
 // 这时候栈或队列也会崩掉
 // https://leetcode.com/problems/coin-change/discuss/251994/C%2B%2B-DFS-%2B-Pruning-beat-99.13-easy-to-understand
class Solution
{
	int ans, len, amount;
	vector<int> coins;

	void dfs(int idx, int left, int num)
	{
		if (idx + 1 == len)
		{
			int curNum = left / coins[idx];
			if (curNum * coins[idx] == left
				&& (ans < 0 || curNum + num < ans))
				ans = curNum + num;
			return;
		}
		// 就算是 1 也顶多这么多
		int total = (ans < 0) ? amount : ans;
		// 首选大的
		for (int i = left / coins[idx]; i >= 0 && num + i <= total; --i)
			dfs(idx + 1, left - i * coins[idx], num + i);
	}

public:
	int coinChange(vector<int>& _Coins, int _Amount)
	{
		if (_Amount == 0) return 0;
		coins.swap(_Coins); // 不能写引用，只能这样了
		amount = _Amount;
		len = static_cast<int>(coins.size());
		std::sort(coins.begin(), coins.end(), std::greater<int>());
		ans = -1;
		dfs(0, amount, 0);
		return ans;
	}
};


int main()
{
	vector<int> coins = { 1, 2, 5 };
	int n = Solution().coinChange(coins, 11);
	printf("coinChange: %d\n", n);
}

