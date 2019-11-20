#include "leetcode.hpp"

/* 680. 验证回文字符串 Ⅱ

给定一个非空字符串 s，最多删除一个字符。
判断是否能成为回文字符串。

示例 1:
输入: "aba"
输出: True

示例 2:
输入: "abca"
输出: True
解释: 你可以删除c字符。

注意:
	字符串只包含从 a-z 的小写字母。字符串的最大长度是50000。
*/


bool valid(string const& str, int L, int R)
{
	for (; L < R; ++L, --R)
	{
		if (str[L] != str[R])
			return false;
	}
	return true;
}


bool validPalindrome(string const& str)
{
	int len = static_cast<int>(str.size());
	int L = 0, R = len - 1;
	for (; L < R; ++L, --R)
	{
		if (str[L] != str[R])
			return valid(str, L + 1, R) || valid(str, L, R - 1);
	}
	return true;
}


int main()
{
	OutExpr(boolstr[validPalindrome("aba")], "%s");
	OutExpr(boolstr[validPalindrome("abca")], "%s");
	OutExpr(boolstr[validPalindrome("abcd")], "%s");
}
