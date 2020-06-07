#include "leetcode.hpp"

/* 316. 去除重复字母

给你一个仅包含小写字母的字符串，请你去除字符串中重复的字母，使得每个字母只出现一次。
需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）。

示例 1:
输入: "bcabc"
输出: "abc"

示例 2:
输入: "cbacdcbc"
输出: "acdb"

注意：该题与 1081 https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters 相同
*/

// https://leetcode.com/problems/remove-duplicate-letters/discuss/76767/C%2B%2B-simple-solution-easy-understanding
// 抄的
string removeDuplicateLetters(string s)
{
	int count[128] = { 0 };
	char have[128] = { 0 };
	string t("0");
	for (char c : s)
		count[c] += 1;
	for (char c : s)
	{
		count[c] -= 1;
		if (have[c])
			continue;
		while ((c < t.back()) && (count[t.back()] > 0))
		{
			have[t.back()] = 0;
			t.pop_back();
		}
		t.push_back(c);
		have[c] = 1;
	}
	return t.substr(1);
}


int main()
{
	OutString(removeDuplicateLetters("bcabc"));
	OutString(removeDuplicateLetters("cbacdcbc"));
}
