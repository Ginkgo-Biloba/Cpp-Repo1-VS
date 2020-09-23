#include "leetcode.hpp"

/* 516. 最长回文子序列

给定一个字符串s，找到其中最长的回文子序列。
可以假设s的最大长度为1000。

示例 1:
输入:
"bbbab"
输出:
4
一个可能的最长回文子序列为 "bbbb"。

示例 2:
输入:
"cbbd"
输出:
2
一个可能的最长回文子序列为 "bb"。
*/

// https://leetcode.com/problems/longest-palindromic-subsequence/discuss/99101/Straight-forward-Java-DP-solution/103130
// 抄的
int longestPalindromeSubseq(string s)
{
	int len = static_cast<int>(s.length());
	auto at = [len](int y, int x) -> int { return y * len + x; };
	vector<int> dp(len * len);

	for (int i = len - 1; i >= 0; --i)
	{
		dp[at(i, i)] = 1;
		for (int k = i + 1; k < len; ++k)
		{
			if (s[i] == s[k])
				dp[at(i, k)] = dp[at(i + 1, k - 1)] + 2;
			else
			{
				dp[at(i, k)] = std::max(
					dp[at(i + 1, k)],
					dp[at(i, k - 1)]);
			}
		}
	}

	return dp[at(0, len - 1)];
}


int main()
{
	OutExpr(longestPalindromeSubseq("bbbab"), "%d");
}
