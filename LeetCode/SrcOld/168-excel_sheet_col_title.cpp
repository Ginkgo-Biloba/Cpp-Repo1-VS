#include "leetcode.hpp"

/* 168. Excel表列名称

给定一个正整数，返回它在 Excel 表中相对应的列名称。

例如，
	1 -> A
	2 -> B
	3 -> C
	...
	26 -> Z
	27 -> AA
	28 -> AB
	...

示例 1:
输入: 1
输出: "A"

示例 2:
输入: 28
输出: "AB"

示例 3:
输入: 701
输出: "ZY"
*/

string convertToTitle(int n)
{
	string s;
	while (n)
	{
		--n;
		s.push_back(static_cast<char>('A' + n % 26));
		n /= 26;
	}
	reverse(s.begin(), s.end());
	return s;
}


int main()
{
	OutString(convertToTitle(1));
	OutString(convertToTitle(28));
	OutString(convertToTitle(701));
}
