#include "leetcode.hpp"

/* 438. 找到字符串中所有字母异位词
给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。
字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

说明：
		字母异位词指字母相同，但排列不同的字符串。
		不考虑答案输出的顺序。

示例 1:
输入:
s: "cbaebabacd" p: "abc"
输出:
[0, 6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。

示例 2:
输入:
s: "abab" p: "ab"
输出:
[0, 1, 2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。
*/

vector<int> findAnagrams(string const& str, string const& pat)
{
	// 既然小于 32768，那么可以 short
	int buf[28];
	short* hs = reinterpret_cast<short*>(buf);
	short* hp = reinterpret_cast<short*>(buf + 14);
	int ls = static_cast<int>(str.size());
	int lp = static_cast<int>(pat.size());
	vector<int> ans;
	if (ls < lp || lp == 0)
		return ans;

	memset(buf, 0, sizeof(buf));
	for (int i = 0; i < lp - 1; ++i)
	{
		++hs[str[i] - 'a'];
		++hp[pat[i] - 'a'];
	}
	int lps1 = lp - 1;
	++hp[pat[lps1] - 'a'];

	for (int i = lps1; i < ls; ++i)
	{
		++hs[str[i] - 'a'];
		int cmp = 0;
		for (; cmp < 14; ++cmp)
		{
			if (buf[cmp] != buf[cmp + 14])
				break;
		}
		if (cmp == 14)
			ans.push_back(i - lps1);
		--hs[str[i - lps1] - 'a'];
	}

	return ans;
}


int main()
{
	output(findAnagrams("cbaebabacd", "abcz"), "findAnagrams");
}
