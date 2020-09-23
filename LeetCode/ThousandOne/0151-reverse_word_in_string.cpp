#include "leetcode.hpp"

/* 151. 翻转字符串里的单词

给定一个字符串，逐个翻转字符串中的每个单词。

示例 1：
输入: "the sky is blue"
输出: "blue is sky the"

示例 2：
输入: "  hello world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。

示例 3：
输入: "a good   example"
输出: "example good a"
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

说明：
	无空格字符构成一个单词。
	输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
	如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

进阶：
请选用 C 语言的用户尝试使用 O(1) 额外空间复杂度的原地解法。
*/

void rev(string& s, int i, int k)
{
	char t;
	for (--k; i < k; ++i, --k)
		t = s[i], s[i] = s[k], s[k] = t;
}

string reverseWords(string s)
{
	int len = static_cast<int>(s.length());
	int i = 0, k = 0;
	while ((k < len) && (s[k] == ' '))
		++k;
	while (k < len)
	{
		if (s[k] != ' ')
			s[i++] = s[k++];
		else
		{
			while ((k < len) && (s[k] == ' '))
				++k;
			if (k < len)
				s[i++] = ' ';
		}
	}
	for (; len > i; --len)
		s.pop_back();
	for (i = 0; i < len;)
	{
		k = i + 1;
		for (; k < len; ++k)
		{
			if (s[k] == ' ')
				break;
		}
		rev(s, i, k);
		i = k + 1;
	}
	rev(s, 0, len);
	return s;
}

int main()
{
	OutString(reverseWords("the sky is blue"));
	OutString(reverseWords("  hello world!  "));
	OutString(reverseWords("a good   example"));
	OutString(reverseWords("example good a"));
}
