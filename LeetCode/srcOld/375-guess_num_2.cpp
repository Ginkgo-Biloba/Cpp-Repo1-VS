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

int guess(int num)
{
	int const val = 7;
	return val < num ? -1 : (num < val ? 1 : 0);
}

int guessNumber(int n)
{
	int i = 1, k = n, m;
	while (i < k)
	{
		m = i + (k - i) / 2;
		int r = guess(m);
		if (r == 1)
			i = m + 1;
		else if (r == -1)
			k = m - 1;
		else
			return m;
	}

	return i;
}

// https://leetcode.com/problems/guess-number-higher-or-lower-ii/discuss/84766/Clarification-on-the-problem-description.-Problem-description-need-to-be-updated
// https://leetcode.com/problems/guess-number-higher-or-lower-ii/discuss/84764/Simple-DP-solution-with-explanation~~/188387
// 抄的

int helper(vector<vector<int>>& dp, int left, int right)
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
		int L = helper(dp, left, mid - 1);
		int R = helper(dp, mid + 1, right);
		int worst = mid + std::max(L, R);
		val = std::min(val, worst);
		if (R <= L)
			break;
	}

	dp[left][right] = val;
	return val;
}

int getMoneyAmount(int n)
{
	vector<vector<int>> dp(n + 1, vector<int>(n + 1));
	int amout = helper(dp, 1, n);
	return amout;
}


int main()
{
	OutExpr(guessNumber(8), "%d");
	OutExpr(getMoneyAmount(10), "%d");
}
