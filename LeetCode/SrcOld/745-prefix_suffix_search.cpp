#include "leetcode.hpp"

/* 745. 前缀和后缀搜索

给定多个 words，words[i] 的权重为 i 。

设计一个类 WordFilter 实现函数WordFilter.f(String prefix, String suffix)。
这个函数将返回具有前缀 prefix 和后缀suffix 的词的最大权重。如果没有这样的词，返回 -1。

例子:
输入:
WordFilter(["apple"])
WordFilter.f("a", "e") // 返回 0
WordFilter.f("b", "") // 返回 -1

注意:
	words的长度在[1, 15000]之间。
	对于每个测试用例，最多会有words.length次对WordFilter.f的调用。
	words[i]的长度在[1, 10]之间。
	prefix, suffix的长度在[0, 10]之前。
	words[i]和prefix, suffix只包含小写字母。
*/

// https://leetcode.com/problems/prefix-and-suffix-search/discuss/110044/Three-ways-to-solve-this-problem-in-Java
// 抄的
class WordFilter
{
	unordered_map<string, vector<int>> pre, suf;

public:
	WordFilter(vector<string>& words)
	{
		int wlen = static_cast<int>(words.size());
		for (int w = 0; w < wlen; ++w)
		{
			int slen = static_cast<int>(words[w].length());
			for (int i = 0; i <= slen; ++i)
			{
				string b = words[w].substr(0, i);
				pre[b].push_back(w);
			}
			for (int i = slen; i >= 0; --i)
			{
				string b = words[w].substr(i);
				suf[b].push_back(w);
			}
		}
	}

	int f(string prefix, string suffix)
	{
		auto itpre = pre.find(prefix);
		auto itsuf = suf.find(suffix);
		if (itpre == pre.end() || itsuf == suf.end())
			return -1;
		vector<int>& p = itpre->second;
		vector<int>& s = itsuf->second;
		int i = static_cast<int>(p.size()) - 1;
		int k = static_cast<int>(s.size()) - 1;
		while (i >= 0 && k >= 0)
		{
			if (p[i] < s[k])
				--k;
			else if (p[i] > s[k])
				--i;
			else
				return p[i];
		}
		return -1;
	}
};


int main()
{
	vector<string> words = { "apple" };
	WordFilter w(words);
	OutExpr(w.f("a", "e"), "%d");
	OutExpr(w.f("h", ""), "%d");
}
