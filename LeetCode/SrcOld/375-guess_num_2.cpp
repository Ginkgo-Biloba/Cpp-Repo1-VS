#include "leetcode.hpp"

/* 375. 猜数字大小 II

我们正在玩一个猜数游戏，游戏规则如下：

我从 1 到 n 之间选择一个数字，你来猜我选了哪个数字。

每次你猜错了，我都会告诉你，我选的数字比你的大了或者小了。

然而，当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。
直到你猜到我选的数字，你才算赢得了这个游戏。

示例:

n = 10, 我选择了8.

第一轮: 你猜我选择的数字是5，我会告诉你，我的数字更大一些，然后你需要支付5块。
第二轮: 你猜是7，我告诉你，我的数字更大一些，你支付7块。
第三轮: 你猜是9，我告诉你，我的数字更小一些，你支付9块。

游戏结束。8 就是我选的数字。

你最终要支付 5 + 7 + 9 = 21 块钱。

给定 n ≥ 1，计算你至少需要拥有多少现金才能确保你能赢得这个游戏。
*/

// 抄的
class Solution
{
	vector<vector<int>> dp;

public:
	int helper(int left, int right)
	{
		int dist = right - left;
		if (dp[left][right] != 0)
			return dp[left][right];

		// 0 或 1 个数字
		if (dist <= 0)
			return 0;

		// 2 个数字和三个数字
		if (dist <= 2)
		{
			dp[left][right] = right - 1;
			return dp[left][right];
		}

		// 四个数字或五个数字
		if (dist <= 4)
		{
			dp[left][right] = (right - 1) + (right - 3);
			return dp[left][right];
		}

		int mid = left + dist / 2;
		int val = INT_MAX;
		for (; mid < right; ++mid)
		{
			int L = helper(left, mid - 1);
			int R = helper(mid + 1, right);
			int worst = mid + max(L, R);
			val = min(val, worst);
			if (R <= L)
				break;
		}

		dp[left][right] = val;
		return val;
	}

	int getMoneyAmount(int n)
	{
		dp.resize(n + 1);
		for (int i = 0; i <= n; ++i)
			dp[i].assign(n + 1, 0);
		int amout = helper(1, n);
		return amout;
	}
};


int main()
{
	Solution s;
	OutExpr(s.getMoneyAmount(10), "%d");
}
