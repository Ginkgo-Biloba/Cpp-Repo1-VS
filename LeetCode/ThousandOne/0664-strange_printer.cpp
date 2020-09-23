#include "leetcode.hpp"

/* 664. 奇怪的打印机

有台奇怪的打印机有以下两个特殊要求：
	打印机每次只能打印同一个字符序列。
	每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。
给定一个只包含小写英文字母的字符串，你的任务是计算这个打印机打印它需要的最少次数。

示例 1:
输入: "aaabbb"
输出: 2
解释: 首先打印 "aaa" 然后打印 "bbb"。

示例 2:
输入: "aba"
输出: 2
解释: 首先打印 "aaa" 然后在第二个位置打印 "b" 覆盖掉原来的字符 'a'。

提示: 输入字符串的长度不会超过 100。
*/

// https://leetcode.com/problems/strange-printer/discuss/106810/Java-O(n3)-DP-Solution-with-Explanation-and-Simple-Optimization
// 抄的
int strangePrinter(string s)
{
	int len = static_cast<int>(s.size());
	if (len == 0)
		return 0;
	int i = 1;
	for (int k = 1; k < len; ++k)
	{
		if (s[k] != s[k - 1])
			s[i++] = s[k];
	}
	len = i;

	// 打印 s[y...x] 所需步数
	vector<int> dp(len * len);
	auto at = [len](int y, int x) -> int
	{
		return y * len + x;
	};
	for (i = 0; i < len; ++i)
	{
		dp[at(i, i)] = 1;
		if (i < len - 1)
			dp[at(i, i + 1)] = 1 + (s[i] != s[i + 1]);
	}

	for (int d = 2; d < len; ++d)
		for (int L = 0; L + d < len; ++L)
		{
			dp[at(L, L + d)] = d + 1;
			for (int m = 0; m < d; ++m)
			{
				int tmp = dp[at(L, L + m)] + dp[at(L + m + 1, L + d)];
				if (s[L + m] == s[L + d])
					--tmp;
				dp[at(L, L + d)] = std::min(dp[at(L, L + d)], tmp);
			}
		}

	return dp[at(0, len - 1)];
}


int main()
{
	OutExpr(strangePrinter("aaabbb"), "%d");
	OutExpr(strangePrinter("abd"), "%d");
}
