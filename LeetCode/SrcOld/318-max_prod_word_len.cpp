#include "leetcode.hpp"

/* 318. 最大单词长度乘积

给定一个字符串数组 words，找到 length(word[i]) * length(word[j]) 的最大值，并且这两个单词不含有公共字母。
你可以认为每个单词只包含小写字母。
如果不存在这样的两个单词，返回 0。

示例 1:
输入: ["abcw","baz","foo","bar","xtfn","abcdef"]
输出: 16
解释: 这两个单词为 "abcw", "xtfn"。

示例 2:
输入: ["a","ab","abc","d","cd","bcd","abcd"]
输出: 4
解释: 这两个单词为 "ab", "cd"。

示例 3:
输入: ["a","aa","aaa","aaaa"]
输出: 0
解释: 不存在这样的两个单词。
*/

int maxProduct(vector<string>& words)
{
	int len = static_cast<int>(words.size());
	vector<pair<int, int>> A;
	for (string& w : words)
	{
		pair<int, int> cur;
		cur.first = static_cast<int>(w.length());
		cur.second = 0;
		for (char c : w)
			cur.second |= (1 << (c - 'a'));
		A.push_back(cur);
	}

	int ans = 0;
	for (int i = len - 1; i > 0; --i)
		for (int h = i - 1; h >= 0; --h)
		{
			if (!(A[i].second & A[h].second))
				ans = max(ans, A[i].first * A[h].first);
		}
	return ans;
}


int main()
{
	vector<string>
		a = { "abcw", "baz", "foo", "bar", "xtfn", "abcdef" },
		b = { "a", "ab", "abc", "d", "cd", "bcd", "abcd" },
		c = { "a", "aa", "aaa", "aaaa" };
	OutExpr(maxProduct(a), "%d");
	OutExpr(maxProduct(b), "%d");
	OutExpr(maxProduct(c), "%d");
}
