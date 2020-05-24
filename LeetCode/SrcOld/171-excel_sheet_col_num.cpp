#include "leetcode.hpp"

/* 171. Excel表列序号

给定一个Excel表格中的列名称，返回其相应的列序号。

例如，
	A -> 1
	B -> 2
	C -> 3
	...
	Z -> 26
	AA -> 27
	AB -> 28
	...

示例 1:
输入: "A"
输出: 1

示例 2:
输入: "AB"
输出: 28

示例 3:
输入: "ZY"
输出: 701

致谢：
特别感谢 @ts 添加此问题并创建所有测试用例。
*/

int titleToNumber(string s)
{
	int len = static_cast<int>(s.size());
	int r = 0, n;
	for (int i = 0; i < len; ++i)
	{
		n = s[i] - 'A';
		r = r * 26 + n + 1;
	}
	return r;
}


int main()
{
	OutExpr(titleToNumber("A"), "%d");
	OutExpr(titleToNumber("AB"), "%d");
	OutExpr(titleToNumber("ZY"), "%d");
}
