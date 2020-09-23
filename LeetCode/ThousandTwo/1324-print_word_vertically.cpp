#include "leetcode.hpp"

/* 1324. 竖直打印单词

给你一个字符串 s。请你按照单词在 s 中的出现顺序将它们全部竖直返回。
单词应该以字符串列表的形式返回，必要时用空格补位，但输出尾部的空格需要删除（不允许尾随空格）。
每个单词只能放在一列上，每一列中也只能有一个单词。

示例 1：
输入：s = "HOW ARE YOU"
输出：["HAY","ORO","WEU"]
解释：每个单词都应该竖直打印。
 "HAY"
 "ORO"
 "WEU"

示例 2：
输入：s = "TO BE OR NOT TO BE"
输出：["TBONTB","OEROOE","   T"]
解释：题目允许使用空格补位，但不允许输出末尾出现空格。
"TBONTB"
"OEROOE"
"   T"

示例 3：
输入：s = "CONTEST IS COMING"
输出：["CIC","OSO","N M","T I","E N","S G","T"]

提示：
	1 <= s.length <= 200
	s 仅含大写英文字母。
	题目数据保证两个单词之间只有一个空格。
*/

vector<string> printVertically(string S)
{
	vector<string> word;
	S.push_back(' ');
	int len = static_cast<int>(S.size());
	int prev = 0, i = 1, wlen = 0;
	for (; i < len; ++i)
		if (S[i] == ' ')
		{
			word.push_back(S.substr(prev, i - prev));
			wlen = max(wlen, i - prev);
			++i;
			prev = i;
		}

	len = static_cast<int>(word.size());
	vector<size_t> idx(len);
	vector<string> ans(wlen);
	for (i = 0; i < wlen; ++i)
	{
		for (int k = 0; k < len; ++k)
		{
			if (idx[k] < word[k].size())
			{
				ans[i].push_back(word[k][idx[k]]);
				++(idx[k]);
			}
			else
				ans[i].push_back(' ');
		}
		while (ans[i].back() == ' ')
			ans[i].pop_back();
	}
	return ans;
}


int main()
{
	string
		a = "HOW ARE YOU",
		b = "TO BE OR NOT TO BE",
		c = "CONTEST IS COMING";
	output(printVertically(a), "\n", "Print Words Vertically");
	output(printVertically(b), "\n", "Print Words Vertically");
	output(printVertically(c), "\n", "Print Words Vertically");
}
