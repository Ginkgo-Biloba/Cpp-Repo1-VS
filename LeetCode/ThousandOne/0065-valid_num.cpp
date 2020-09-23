#include "leetcode.hpp"

/* 65. 有效数字

验证给定的字符串是否可以解释为十进制数字。

例如:

"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

说明: 我们有意将问题陈述地比较模糊。
在实现代码之前，你应当事先思考所有可能的情况。
这里给出一份可能存在于有效十进制数字中的字符列表：
	数字 0-9
	指数 - "e"
	正/负号 - "+"/"-"
	小数点 - "."

当然，在输入中，这些字符的上下文也很重要。

更新于 2015-02-10:
C++函数的形式已经更新了。
如果你仍然看见你的函数接收 const char * 类型的参数，请点击重载按钮重置你的代码。
*/

// https://leetcode.com/problems/valid-number/discuss/23762/A-simple-solution-in-cpp
// 抄的
bool isNumber(string str)
{
	char const* s = str.c_str();
	int i = 0;

	while (s[i] == ' ')
		++i;
	if (s[i] == '+' || s[i] == '-')
		++i;

	int nm = 0, pt = 0;
	while ((isdigit(s[i])) || (s[i] == '.'))
	{
		if (s[i] == '.')
			++pt;
		else
			++nm;
		++i;
	}
	if (pt > 1 || nm < 1)
		return false;
	if ((s[i] == 'e'))
	{
		++i;
		if (s[i] == '+' || s[i] == '-')
			++i;
		nm = 0;
		while (isdigit(s[i]))
		{
			++i;
			++nm;
		}
		if (nm < 1)
			return false;
	}

	while (s[i] == ' ')
		++i;
	return s[i] == 0;
}


int main()
{
	OutBool(isNumber("0"));
	OutBool(isNumber(" 0.1 "));
	OutBool(isNumber("abc"));
	OutBool(isNumber("1 a"));
	OutBool(isNumber("2e10"));
	OutBool(isNumber(" -90e3   "));
	OutBool(isNumber(" 1e"));
	OutBool(isNumber("e3"));
	OutBool(isNumber(" 6e-1"));
	OutBool(isNumber(" 99e2.5 "));
	OutBool(isNumber("53.5e93"));
	OutBool(isNumber(" --6 "));
	OutBool(isNumber("-+3"));
	OutBool(isNumber("95a54e53"));
}
