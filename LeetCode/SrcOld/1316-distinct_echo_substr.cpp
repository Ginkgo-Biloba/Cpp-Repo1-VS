#include "leetcode.hpp"

/* 1316. 不同的循环子字符串

给你一个字符串 text ，请你返回满足下述条件的 不同 非空子字符串的数目：
	可以写成某个字符串与其自身相连接的形式（即，可以写为 a + a，其中 a 是某个字符串）。

例如，abcabc 就是 abc 和它自身连接形成的。

示例 1：
输入：text = "abcabcabc"
输出：3
解释：3 个子字符串分别为 "abcabc"，"bcabca" 和 "cabcab" 。

示例 2：
输入：text = "leetcodeleetcode"
输出：2
解释：2 个子字符串为 "ee" 和 "leetcodeleetcode" 。

提示：
	1 <= text.length <= 2000
	text 只包含小写英文字母。
*/

// https://leetcode.com/problems/distinct-echo-substrings/discuss/492704/Easy-Sliding-Window-Rolling-Counter
// http://blog.sandwormz.com/2010/11/rolling-counter-algorithm-pattern.html
// 抄的
int distinctEchoSubstrings(string text)
{
	int size = static_cast<int>(text.size());
	int sum = 0;
	unordered_set<string> M;
	for (int len = 1; len <= size / 2; ++len)
	{
		M.clear();
		int L = 0, R = len, count = 0;
		for (; L < size - len; ++L, ++R)
		{
			if (text[L] == text[R])
			{
				++count;
				if (count == len)
				{
					M.insert(text.substr(L - len + 1, len));
					--count;
				}
			}
			else
				count = 0;
		}
		sum += static_cast<int>(M.size());
	}
	return sum;
}

int main()
{
	OutExpr(distinctEchoSubstrings("abcabcabc"), "%d");
	OutExpr(distinctEchoSubstrings("leetcodeleetcode"), "%d");
}
