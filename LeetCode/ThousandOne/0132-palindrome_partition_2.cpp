#include "leetcode.hpp"

/* 132. 分割回文串 II

给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

返回符合要求的最少分割次数。

示例:
输入: "aab"
输出: 1
解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
*/

// https://leetcode.com/problems/palindrome-partitioning-ii/discuss/42212/Two-C%2B%2B-versions-given-(one-DP-28ms-one-Manancher-like-algorithm-10-ms)
// 抄的
int minCut(string s)
{
	int len = static_cast<int>(s.size());
	if (len <= 1)
		return 0;
	vector<int> dp(len + 1);
	for (int i = 0; i <= len; ++i)
		dp[i] = i - 1;
	for (int i = 1; i < len; ++i)
	{
		// odd length
		for (int k = 0;
			(k <= i) && (k + i < len) && (s[i - k] == s[i + k]);
			++k)
			dp[i + k + 1] = min(dp[i + k + 1], 1 + dp[i - k]);
		// even length
		for (int k = 0;
			(k + 1 <= i) && (k + i < len) && (s[i - k - 1] == s[i + k]);
			++k)
			dp[i + k + 1] = min(dp[i + k + 1], 1 + dp[i - k - 1]);
	}
	return dp[len];
}


int main()
{
	OutExpr(minCut("aab"), "%d");
}
