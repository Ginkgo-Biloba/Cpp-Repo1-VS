#include "leetcode.hpp"

/* 434. 字符串中的单词数

统计字符串中的单词个数，这里的单词指的是连续的不是空格的字符。
请注意，你可以假定字符串里不包括任何不可打印的字符。

示例:
输入: "Hello, my name is John"
输出: 5
*/

int countSegments(string const& s)
{
	size_t len = s.length();
	int count = (len && (s[0] != ' '));
	for (size_t i = 1; i < len; ++i)
		count += ((s[i] != ' ') && (s[i - 1] == ' '));
	return count;
}


int main()
{
	OutExpr(countSegments(" a, k "), "%d");
}
