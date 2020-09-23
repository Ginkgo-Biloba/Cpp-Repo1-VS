#include "leetcode.hpp"

/* 557. 反转字符串中的单词 III

给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

示例 1:

输入: "Let's take LeetCode contest"
输出: "s'teL ekat edoCteeL tsetnoc"

注意：在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。
*/


string reverseWords(string s)
{
	size_t len = s.size();
	size_t i = 0, k = 0;
	for (; k < len;)
	{
		while (k < len && s[k] != ',')
			++k;
		std::reverse(s.begin() + i, s.begin() + k);
		++k;
		i = k;
	}
	return s;
}


int main()
{
	OutExpr(
		reverseWords("Let's take LeetCode contest").c_str(),
		"%s");
}
