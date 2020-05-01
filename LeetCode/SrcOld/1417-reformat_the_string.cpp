#include "leetcode.hpp"

/* 1417. 重新格式化字符串

给你一个混合了数字和字母的字符串 s，其中的字母均为小写英文字母。

请你将该字符串重新格式化，使得任意两个相邻字符的类型都不同。
也就是说，字母后面应该跟着数字，而数字后面应该跟着字母。

请你返回 重新格式化后 的字符串；如果无法按要求重新格式化，则返回一个 空字符串 。

示例 1：
输入：s = "a0b1c2"
输出："0a1b2c"
解释："0a1b2c" 中任意两个相邻字符的类型都不同。 "a0b1c2", "0a1b2c", "0c2a1b" 也是满足题目要求的答案。

示例 2：
输入：s = "leetcode"
输出：""
解释："leetcode" 中只有字母，所以无法满足重新格式化的条件。

示例 3：
输入：s = "1229857369"
输出：""
解释："1229857369" 中只有数字，所以无法满足重新格式化的条件。

示例 4：
输入：s = "covid2019"
输出："c2o0v1i9d"

示例 5：
输入：s = "ab123"
输出："1a2b3"

提示：
	1 <= s.length <= 500
	s 仅由小写英文字母和/或数字组成。
*/


string reformat(string s)
{
	vector<char> c, d;
	for (char i : s)
	{
		if (isdigit(i))
			d.push_back(i);
		else
			c.push_back(i);
	}
	s.clear();
	if ((c.size() > d.size() + 1)
		|| (d.size() > c.size() + 1))
		return s;
	if (c.size() > d.size())
	{
		s.push_back(c.back());
		c.pop_back();
	}
	while (!d.empty() && !c.empty())
	{
		s.push_back(d.back());
		s.push_back(c.back());
		d.pop_back();
		c.pop_back();
	}
	if (d.size())
		s.push_back(d.back());
	return s;
}


int main()
{
	OutString(reformat("a0b1c2"));
	OutString(reformat("leetcode"));
	OutString(reformat("1229857369"));
	OutString(reformat("covid2019"));
	OutString(reformat("ab123"));
}
