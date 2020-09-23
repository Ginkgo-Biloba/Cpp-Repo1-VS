#include "leetcode.hpp"

/* 30. 串联所有单词的子串

给定一个字符串 s 和一些长度相同的单词 words。
找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

示例 1：
输入：
	s = "barfoothefoobarman",
	words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。

示例 2：
输入：
	s = "wordgoodgoodgoodbestword",
	words = ["word","good","best","word"]
输出：[]
*/

vector<int> findSubstring(string const& str, vector<string> const& words)
{
	vector<int> ans;
	if (str.empty() || words.empty()) return ans;

	int s, slen = static_cast<int>(str.length());
	int w, ws = static_cast<int>(words.size());
	int wlen = static_cast<int>(words[0].length());
	unordered_map<string, int> counts; // 每个单词的期望出现次数
	unordered_map<string, int> seen; // 实际看到的每个单词的次数

	for (string const& wd : words)
		counts[wd]++;
	slen -= (wlen * ws);
	for (s = 0; s <= slen; s++)
	{
		seen.clear();
		for (w = 0; w < ws; w++)
		{
			string wd = str.substr(s + w * wlen, wlen);
			if (counts.find(wd) != counts.end())
			{
				seen[wd]++;
				if (seen[wd] > counts[wd])
					break;
			}
			else
				break;
		}
		if (w == ws)
			ans.push_back(s);
	}

	return ans;
}

int main()
{}
