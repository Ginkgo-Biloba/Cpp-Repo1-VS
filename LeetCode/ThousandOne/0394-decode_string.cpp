#include "leetcode.hpp"

/* 394. 字符串解码

给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。
注意 k 保证为正整数。

你可以认为输入字符串总是有效的；
输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k。
例如不会出现像 3a 或 2[4] 的输入。

示例:
s = "3[a]2[bc]", 返回 "aaabcbc".
s = "3[a2[c]]", 返回 "accaccacc".
s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".
*/

string decodeString(string const& E)
{
	size_t len = E.length();
	string D;
	vector<int> cnt;
	vector<string> rep;

	for (size_t i = 0; i < len;)
	{
		if (isdigit(E[i]))
		{
			int n = E[i] - '0';
			size_t k = i + 1;
			// 保证符合要求，不用检查越界
			for (; isdigit(E[k]); ++k)
				n = n * 10 + (E[k] - '0');
			cnt.push_back(n);
			i = k;
		}
		else if (E[i] == '[')
		{
			string cur;
			size_t k = i + 1;
			for (; !isdigit(E[k]) && E[k] != ']'; ++k)
				cur.push_back(E[k]);
			rep.push_back(cur);
			i = k;
		}
		else if (E[i] == ']')
		{
			string cur;
			int n = cnt.back();
			cur.reserve(rep.back().size() * n);
			while (n--)
				cur += rep.back();
			rep.pop_back();
			cnt.pop_back();
			if (rep.empty())
				D += cur;
			else
				rep.back() += cur;
			++i;
		}
		// 又没说不能出现 **&*&￥@！%%&*&（* 这种
		else // if (isalpha(E[i]))
		{
			bool out = rep.empty();
			for (; i < len && !isdigit(E[i]) && E[i] != ']'; ++i)
			{
				if (out)
					D.push_back(E[i]);
				else
					rep.back().push_back(E[i]);
			}
		}
	}

	return D;
}


int main()
{
	OutExpr(decodeString("2[b4[F]c]").c_str(), "%s");
	OutExpr(decodeString("3[a]2[bc]").c_str(), "%s");
	OutExpr(decodeString("3[a2[c]]").c_str(), "%s");
	OutExpr(decodeString("2[abc]3[cd]ef").c_str(), "%s");
}
