#include "leetcode.hpp"

/* 5. 最长回文子串

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。

示例 2：
输入: "cbbd"
输出: "bb"
*/

string longestPalindrome(string s)
{
	int len = static_cast<int>(s.size());
	int ans = 1, idx = 0;
	vector<char> dp(len * len);
	auto at = [len](int a, int b) { return a * len + b; };
	for (int h = 0; h < len; ++h)
	{
		dp[at(h, h)] = 1;
		// 处理 d = 2 时的情况
		if (h < len - 1)
			dp[at(h + 1, h)] = 1;
	}
	for (int d = 2; d <= len; ++d)
		for (int h = 0; h <= len - d; ++h)
		{
			int i = h + d - 1;
			bool b = (dp[at(h + 1, i - 1)] && (s[h] == s[i]));
			dp[at(h, i)] = b;
			if (b)
			{
				ans = d;
				idx = h;
			}
		}
	return s.substr(idx, ans);
}

int main()
{
	OutString(longestPalindrome("babad"));
	OutString(longestPalindrome("cbbd"));
	OutString(longestPalindrome("bb"));
	OutString(longestPalindrome("abcda"));
}
