#include "leetcode.hpp"

/* 1392. 最长快乐前缀

「快乐前缀」是在原字符串中既是 非空 前缀也是后缀（不包括原字符串自身）的字符串。

给你一个字符串 s，请你返回它的 最长快乐前缀。

如果不存在满足题意的前缀，则返回一个空字符串。

示例 1：
输入：s = "level"
输出："l"
解释：不包括 s 自己，一共有 4 个前缀（"l", "le", "lev", "leve"）和 4 个后缀（"l", "el", "vel", "evel"）。最长的既是前缀也是后缀的字符串是 "l" 。

示例 2：
输入：s = "ababab"
输出："abab"
解释："abab" 是最长的既是前缀也是后缀的字符串。题目允许前后缀在原字符串中重叠。

示例 3：
输入：s = "leetcodeleet"
输出："leet"

示例 4：
输入：s = "a"
输出：""

提示：
	1 <= s.length <= 10^5
	s 只含有小写英文字母
*/

string longestPrefix_org(string S)
{
	S.push_back('.');
	int len = static_cast<int>(S.size());
	vector<int> N(len);
	int i = 0, k = -1;
	N[0] = -1;
	while (i < len - 1)
	{
		if (k == -1 || S[k] == S[i])
		{
			++i;
			++k;
			N[i] = k;
		}
		else
			k = N[k];
	}
	return S.substr(0, N[len - 1]);
}

// https://leetcode.com/problems/longest-happy-prefix/discuss/547446/C%2B%2BJava-with-picture-incremental-hash-and-KMP
// 抄的
string longestPrefix(string s)
{
	int len = static_cast<int>(s.size());
	vector<int> dp(len);
	int h = 0, i = 1;
	for (; i < len; ++i)
	{
		if (s[h] == s[i])
			dp[i] = ++h;
		else if (h > 0)
		{
			h = dp[h - 1];
			--i;
		}
	}
	return s.substr(0, h);
}


int main()
{
	OutString(longestPrefix("level"));
	OutString(longestPrefix("ababab"));
	OutString(longestPrefix("leetcodeleet"));
	OutString(longestPrefix("a"));
}
