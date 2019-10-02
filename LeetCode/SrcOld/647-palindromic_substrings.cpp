#include "leetcode.hpp"

/* 647. 回文子串

给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。

示例 1:
输入: "abc"
输出: 3
解释: 三个回文子串: "a", "b", "c".

示例 2:
输入: "aaa"
输出: 6
说明: 6个回文子串: "a", "a", "a", "aa", "aa", "aaa".

注意:
	输入的字符串长度不会超过1000。
*/

// https://leetcode.com/problems/palindromic-substrings/discuss/105688/Very-Simple-Java-Solution-with-Detail-Explanation
// 抄的
int palindrome(string const& str, int L, int R)
{
	int count = 0;
	int len = static_cast<int>(str.length());
	while (L >= 0 && R < len && str[L] == str[R])
	{
		--L;
		++R;
		++count;
	}
	return count;
}

int countSubstrings(string const& str)
{
	int len = static_cast<int>(str.length());
	int count = 0;
	for (int i = 0; i < len; ++i)
	{
		count += palindrome(str, i, i);
		count += palindrome(str, i, i + 1);
	}
	return count;
}


int main()
{
	OutExpr(countSubstrings("abc"), "%d");
	OutExpr(countSubstrings("aaa"), "%d");
}
