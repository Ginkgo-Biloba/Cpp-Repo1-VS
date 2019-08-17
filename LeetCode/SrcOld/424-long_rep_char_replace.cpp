#include "leetcode.hpp"

/* 424. 替换后的最长重复字符
给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。
注意:
字符串长度 和 k 不会超过 104。

示例 1:
输入:
s = "ABAB", k = 2
输出:
4
解释:
用两个'A'替换为两个'B',反之亦然。

示例 2:
输入:
s = "AABABBA", k = 1
输出:
4
解释:
将中间的一个'A'替换为'B',字符串变为 "AABBBBA"。
子串 "BBBB" 有最长重复字母, 答案为 4。
*/

// https://leetcode.com/problems/longest-repeating-character-replacement/discuss/91271/Java-12-lines-O(n)-sliding-window-solution-with-explanation
// 抄的
int characterReplacement(string const& s, int k)
{
	int len = static_cast<int>(s.length());
	int count[128];
	memset(count, 0, sizeof(count));
	int left = 0, maxlen = 0, maxcount = 0;
	for (int right = 0; right < len; ++right)
	{
		int c = s[right];
		++count[c];
		maxcount = std::max(maxcount, count[c]);
		while (right - left + 1 - maxcount > k)
		{
			--count[s[left]];
			++left;
		}
		maxlen = std::max(maxlen, right - left + 1);
	}
	return maxlen;
}


int main()
{
	OutExpr(characterReplacement("AAZZ", 2), "%d");
}
