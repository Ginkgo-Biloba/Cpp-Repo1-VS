#include "leetcode.hpp"

/* 290. 单词规律

给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:
输入: pattern = "abba", str = "dog cat cat dog"
输出: true

示例 2:
输入:pattern = "abba", str = "dog cat cat fish"
输出: false

示例 3:
输入: pattern = "aaaa", str = "dog cat cat dog"
输出: false

示例 4:
输入: pattern = "abba", str = "dog dog dog dog"
输出: false

说明:
你可以假设 pattern 只包含小写字母， str 包含了由单个空格分隔的小写字母。
*/

bool wordPattern(string pattern, string str)
{
	vector<string> words;
	size_t len = str.size();
	for (size_t i = 0; i < len;)
	{
		size_t k = i + 1;
		for (; k < len; ++k)
		{
			if (str[k] == ' ')
				break;
		}
		words.push_back(str.substr(i, k - i));
		i = k + 1;
	}
	len = words.size();
	unordered_map<char, string> A;
	unordered_map<string, char> B;
	if (len != pattern.length())
		return false;
	for (size_t i = 0; i < len; ++i)
	{
		auto a = A.find(pattern[i]);
		auto b = B.find(words[i]);
		if (a == A.end() && b == B.end())
		{
			A.emplace(pattern[i], words[i]);
			B.emplace(words[i], pattern[i]);
		}
		else if ((a == A.end()) ^ (b == B.end()))
			return false;
		else if ((a->second != b->first) || (b->second != a->first))
			return false;
	}
	return true;
}


int main()
{
	OutBool(wordPattern("abba", "dog cat cat dog"));
	OutBool(wordPattern("abba", "dog cat cat fish"));
	OutBool(wordPattern("aaaa", "dog cat cat dog"));
	OutBool(wordPattern("abba", "dog dog dog dog"));
}
