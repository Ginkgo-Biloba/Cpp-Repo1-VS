#include "leetcode.hpp"

/* 884. 两句话中的不常见单词

给定两个句子 A 和 B。
句子是一串由空格分隔的单词。每个单词仅由小写字母组成。

如果一个单词在其中一个句子中只出现一次，在另一个句子中却没有出现，那么这个单词就是不常见的。

返回所有不常用单词的列表。

您可以按任何顺序返回列表。

示例 1：
输入：A = "this apple is sweet", B = "this apple is sour"
输出：["sweet","sour"]

示例 2：
输入：A = "apple apple", B = "banana"
输出：["banana"]

提示：
	0 <= A.length <= 200
	0 <= B.length <= 200
	A 和 B 都只包含空格和小写字母。
*/

string getWord(string const& s, size_t& i)
{
	size_t h = i, len = s.size();
	while (h < len && s[h] == ' ')
		++h;
	for (i = h + 1; i < len; ++i)
	{
		if (s[i] == ' ')
			return s.substr(h, i - h);
	}
	return string();
}

vector<string> uncommonFromSentences(string A, string B)
{
	string s = A + ' ' + B + ' ';
	size_t len = s.size();
	unordered_map<string, int> um;
	vector<string> ans;

	for (size_t i = 0; i < len;)
	{
		A = getWord(s, i);
		if (!A.empty())
			um[A] += 1;
	}

	for (auto const& kv : um)
	{
		if (kv.second == 1)
			ans.push_back(kv.first);
	}
	return ans;
}


int main()
{
	output(
		uncommonFromSentences("this apple is sweet", "this apple is sour"),
		" | ", "uncommonFromSentences");
	output(
		uncommonFromSentences("apple apple", "banana"),
		" | ", "uncommonFromSentences");
}
