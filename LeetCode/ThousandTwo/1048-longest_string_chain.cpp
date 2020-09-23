#include "leetcode.hpp"

/* 1048. 最长字符串链

给出一个单词列表，其中每个单词都由小写英文字母组成。

如果我们可以在 word1 的任何地方添加一个字母使其变成 word2，那么我们认为 word1 是 word2 的前身。
例如，"abc" 是 "abac" 的前身。

词链是单词 [word_1, word_2, ..., word_k] 组成的序列，k >= 1，其中 word_1 是 word_2 的前身，word_2 是 word_3 的前身，依此类推。

从给定单词列表 words 中选择单词组成词链，返回词链的最长可能长度。

示例：
输入：["a","b","ba","bca","bda","bdca"]
输出：4
解释：最长单词链之一为 "a","ba","bda","bdca"。

提示：
	1 <= words.length <= 1000
	1 <= words[i].length <= 16
	words[i] 仅由小写英文字母组成。
*/

// https://leetcode.com/problems/longest-string-chain/discuss/294890/C%2B%2BJavaPython-DP-Solution
// 抄的
int longestStrChain(vector<string>& words)
{
	sort(words.begin(), words.end(),
		[](string const& a, string const& b)
	{
		return a.size() < b.size();
	});

	int ans = 0;
	unordered_map<string, int> m;
	for (string const& w : words)
	{
		int best = 1;
		int len = static_cast<int>(w.size());
		for (int i = 0; i < len; ++i)
		{
			string s = w.substr(0, i) + w.substr(i + 1);
			auto it = m.find(s);
			if (it != m.end())
				best = max(best, it->second + 1);
		}
		m[w] = best;
		ans = max(ans, best);
	}
	return ans;
}

int main()
{
	vector<string> a = { "a", "b", "ba", "bca", "bda", "bdca" };

	OutExpr(longestStrChain(a), "%d");
}
