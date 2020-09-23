#include "leetcode.hpp"

/* 824. 山羊拉丁文

给定一个由空格分割单词的句子 S。每个单词只包含大写或小写字母。

我们要将句子转换为 “Goat Latin”（一种类似于 猪拉丁文 - Pig Latin 的虚构语言）。

山羊拉丁文的规则如下：

	如果单词以元音开头（a, e, i, o, u），在单词后添加"ma"。
	例如，单词"apple"变为"applema"。

	如果单词以辅音字母开头（即非元音字母），移除第一个字符并将它放到末尾，之后再添加"ma"。
	例如，单词"goat"变为"oatgma"。

	根据单词在句子中的索引，在单词最后添加与索引相同数量的字母'a'，索引从1开始。
	例如，在第一个单词后添加"a"，在第二个单词后添加"aa"，以此类推。

返回将 S 转换为山羊拉丁文后的句子。

示例 1:
输入: "I speak Goat Latin"
输出: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"

示例 2:
输入: "The quick brown fox jumped over the lazy dog"
输出: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"

说明:
	S 中仅包含大小写字母和空格。单词间有且仅有一个空格。
	1 <= S.length <= 150。
*/

bool isvowel(char c)
{
	return false
		|| c == 'a' || c == 'A'
		|| c == 'e' || c == 'E'
		|| c == 'i' || c == 'I'
		|| c == 'o' || c == 'O'
		|| c == 'u' || c == 'U';
}


string toGoatLatin(string S)
{
	S.push_back(' ');
	int len = static_cast<int>(S.size());
	int L = 0, R, no = 1;
	string D, cur;

	while (L < len)
	{
		R = L + 1;
		while (R < len && S[R] != ' ')
			++R;
		if (isvowel(S[L]))
			cur = S.substr(L, R - L);
		else
		{
			cur = S.substr(L + 1, R - L - 1);
			cur.push_back(S[L]);
		}
		cur.reserve(R - L + no + 4);
		cur += "ma";
		for (int i = 0; i < no; ++i)
			cur.push_back('a');
		cur.push_back(' ');
		D += cur;
		++no;
		L = R + 1;
	}

	D.pop_back();
	return D;
}


int main()
{
	string
		a("I speak Goat Latin"),
		b("The quick brown fox jumped over the lazy dog");
	// 那个 . 为了验证结尾没有多余的空格
	OutExpr(toGoatLatin(a).c_str(), "%s.");
	OutExpr(toGoatLatin(b).c_str(), "%s.");
}
