#include "leetcode.hpp"

/* 1358. 包含所有三种字符的子字符串数目

给你一个字符串 s ，它只包含三种字符 a, b 和 c 。

请你返回 a，b 和 c 都 至少 出现过一次的子字符串数目。

示例 1：
输入：s = "abcabc"
输出：10
解释：包含 a，b 和 c 各至少一次的子字符串为 "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" 和 "abc" (相同字符串算多次)。

示例 2：
输入：s = "aaacb"
输出：3
解释：包含 a，b 和 c 各至少一次的子字符串为 "aaacb", "aacb" 和 "acb" 。

示例 3：
输入：s = "abc"
输出：1

提示：
	3 <= s.length <= 5 x 10^4
	s 只包含字符 a，b 和 c 。
*/

// https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/discuss/516977/JavaC%2B%2BPython-Easy-and-Concise
// 抄的
int numberOfSubstrings(string s)
{
	int len = static_cast<int>(s.size());
	int n['d'] = { 0 };
	int h = 0, i = 0, ans = 0;
	for (; i < len; ++i)
	{
		n[s[i]] += 1;
		while (n['a'] > 0 && n['b'] > 0 && n['c'] > 0)
		{
			n[s[h]] -= 1;
			++h;
		}
		ans += h;
	}
	return ans;
}


int main()
{
	OutExpr(numberOfSubstrings("abcabc"), "%d");
	OutExpr(numberOfSubstrings("aaacb"), "%d");
	OutExpr(numberOfSubstrings("abc"), "%d");
}
