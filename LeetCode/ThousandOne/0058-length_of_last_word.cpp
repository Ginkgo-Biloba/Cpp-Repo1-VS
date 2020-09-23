#include "leetcode.hpp"

/* 58. 最后一个单词的长度

给定一个仅包含大小写字母和空格 ' ' 的字符串 s，返回其最后一个单词的长度。
如果字符串从左向右滚动显示，那么最后一个单词就是最后出现的单词。

如果不存在最后一个单词，请返回 0 。

说明：一个单词是指仅由字母组成、不包含任何空格字符的 最大子字符串。

示例:
输入: "Hello World"
输出: 5
*/

int lengthOfLastWord(string s)
{
	while (s.length() && s.back() == ' ')
		s.pop_back();
	size_t i = s.find_last_of(' ');
	if (i == string::npos)
		i = -1;
	i = s.length() - i - 1;
	return static_cast<int>(i);
}


int main()
{
	OutExpr(lengthOfLastWord("Hello World"), "%d");
	OutExpr(lengthOfLastWord("HelloWorld"), "%d");
	OutExpr(lengthOfLastWord(""), "%d");
}
