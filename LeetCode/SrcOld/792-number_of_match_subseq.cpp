#include "leetcode.hpp"

/* 792. 匹配子序列的单词数

给定字符串 S 和单词字典 words, 求 words[i] 中是 S 的子序列的单词个数。

示例:
输入:
S = "abcde"
words = ["a", "bb", "acd", "ace"]
输出: 3
解释: 有三个是 S 的子序列的单词: "a", "acd", "ace"。

注意:
	所有在words和 S 里的单词都只由小写字母组成。
	S 的长度在 [1, 50000]。
	words 的长度在 [1, 5000]。
	words[i]的长度在[1, 50]。
*/

typedef unsigned short ushort;

struct vec26
{
	ushort val[26];
	ushort& operator[](int i) { return val[i]; }
	void set(ushort v)
	{
		for (int i = 0; i < 26; ++i)
			val[i] = v;
	}
};

int numMatchingSubseq(string S, vector<string>& words)
{
	int const A = 'a';
	int ans = 0;
	int len = static_cast<int>(S.size());
	vector<vec26> info(len + 1);
	info.back().set(static_cast<ushort>(len + 1));

	for (int i = len - 1; i >= 0; --i)
	{
		info[i] = info[i + 1];
		info[i][S[i] - A] = static_cast<ushort>(i + 1);
	}

	for (string& w : words)
	{
		int find = 1, i = 0;
		for (char c : w)
		{
			i = info[i][c - A];
			if (i == len + 1)
			{
				find = 0;
				break;
			}
		}
		ans += find;
	}
	return ans;
}


int main()
{
	vector<string> w0 = { "a", "bb", "acd", "ace" };
	OutExpr(numMatchingSubseq("abcde", w0), "%d");
}
