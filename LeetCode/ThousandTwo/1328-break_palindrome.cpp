#include "leetcode.hpp"

/* 1328. 破坏回文串

给你一个回文字符串 palindrome，请你将其中 一个 字符用任意小写英文字母替换，使得结果字符串的字典序最小，且 不是 回文串。

请你返回结果字符串。如果无法做到，则返回一个空串。

示例 1：
输入：palindrome = "abccba"
输出："aaccba"

示例 2：
输入：palindrome = "a"
输出：""

提示：
	1 <= palindrome.length <= 1000
	palindrome 只包含小写英文字母。
*/


string breakPalindrome(string S)
{
	int len = static_cast<int>(S.size());
	int i = 0;
	for (i = 0; i < len / 2; ++i)
	{
		if (S[i] != 'a')
			break;
	}
	if (i == len / 2)
	{
		if ((len & 1) && (S[i] == 'b'))
			S[len - 1] = 'b';
		else
			S[i] = 'b';
		int L = 0, R = len - 1;
		while ((L < R) && (S[L] == S[R]))
		{
			++L;
			--R;
		}
		if (L == R)
			S.clear();
		return S;
	}
	S[i] = 'a';
	return S;
}

int main()
{
	OutString(breakPalindrome("abccba"));
	OutString(breakPalindrome("a"));
	OutString(breakPalindrome("aabaa"));
}
