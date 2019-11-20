#include "leetcode.hpp"

/* 678. 有效的括号字符串

给定一个只包含三种字符的字符串：（ ，） 和 *，写一个函数来检验这个字符串是否为有效字符串。
有效字符串具有如下规则：
	任何左括号 ( 必须有相应的右括号 )。
	任何右括号 ) 必须有相应的左括号 ( 。
	左括号 ( 必须在对应的右括号之前 )。
	* 可以被视为单个右括号 ) ，或单个左括号 ( ，或一个空字符串。
	一个空字符串也被视为有效字符串。

示例 1:
输入: "()"
输出: True

示例 2:
输入: "(*)"
输出: True

示例 3:
输入: "(*))"
输出: True

注意:
	字符串大小将在 [1，100] 范围内。
*/

// https://leetcode.com/problems/valid-parenthesis-string/discuss/107611/Very-concise-C%2B%2B-solution-with-explaination.-No-DP
// 抄的
bool checkValidString(string s)
{
	// 未匹配的 ( 的数量范围
	int lo = 0, hi = 0;
	for (char c : s)
	{
		if (c == '(')
		{
			++lo;
			++hi;
		}
		else if (c == ')')
		{
			--lo;
			--hi;
		}
		else // c == '*'
		{
			--lo;
			++hi;
		}
		lo = std::max(lo, 0);
		if (hi < 0)
			return false;
	}
	return lo == 0;
}


int main()
{
	OutExpr(boolstr[checkValidString("")], "%s");
	OutExpr(boolstr[checkValidString("()")], "%s");
	OutExpr(boolstr[checkValidString("(*)")], "%s");
	OutExpr(boolstr[checkValidString("(*))")], "%s");
	OutExpr(boolstr[checkValidString("((*)")], "%s");
}
