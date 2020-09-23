#include "leetcode.hpp"

/* 140. 单词拆分 II

给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，在字符串中增加空格来构建一个句子，使得句子中所有的单词都在词典中。
返回所有这些可能的句子。

说明：
	分隔时可以重复使用字典中的单词。
	你可以假设字典中没有重复的单词。

示例 1：
输入:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
输出:
[
	"cats and dog",
	"cat sand dog"
]

示例 2：
输入:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
输出:
[
	"pine apple pen apple",
	"pineapple pen apple",
	"pine applepen apple"
]
解释: 注意你可以重复使用字典中的单词。

示例 3：
输入:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
输出:
[]
*/

// https://leetcode.com/problems/word-break-ii/discuss/44178/11ms-C%2B%2B-solution-(concise)
// 抄的
class Solution
{
	unordered_map<string, vector<string>> m;
	unordered_set<string> t;

	vector<string> combine(string const& word, vector<string> prev)
	{
		for (string& p : prev)
		{
			p.push_back(' ');
			p += word;
		}
		return prev;
	}

	vector<string> dfs(string s)
	{
		vector<string> r;
		auto it = m.find(s);
		if (it != m.end())
			return it->second;
		if (t.find(s) != t.end())
			r.push_back(s);
		int len = static_cast<int>(s.length());
		for (int i = 1; i < len; ++i)
		{
			string w = s.substr(i);
			if (t.find(w) != t.end())
			{
				vector<string> left = combine(w, dfs(s.substr(0, i)));
				int dd = static_cast<int>(left.size());
				for (int d = 0; d < dd; ++d)
					r.push_back(move(left[d]));
			}
		}
		m[s] = r;
		return r;
	}

public:
	vector<string> wordBreak(string s, vector<string>& dict)
	{
		m.clear();
		unordered_set<string>(dict.begin(), dict.end()).swap(t);
		vector<string> r = dfs(s);
		return r;
	}
};


int main()
{
	vector<string>
		a = { "leet", "code" },
		b = { "apple", "pen" },
		c = { "cats", "dog", "sand", "and", "cat" };
	Solution s;
	output(s.wordBreak("leetcode", a), "\n", "Word Break II");
	output(s.wordBreak("applepenapple", b), "\n", "Word Break II");
	output(s.wordBreak("catsandog", c), "\n", "Word Break II");
	output(s.wordBreak("catsanddog", c), "\n", "Word Break II");
}
