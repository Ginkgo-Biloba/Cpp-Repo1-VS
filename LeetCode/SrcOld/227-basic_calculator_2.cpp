#include "leetcode.hpp"

/* 227. 基本计算器 II

实现一个基本的计算器来计算一个简单的字符串表达式的值。

字符串表达式仅包含非负整数，+， - ，*，/ 四种运算符和空格。
整数除法仅保留整数部分。

示例 1:
输入: "3+2*2"
输出: 7

示例 2:
输入: " 3/2 "
输出: 1

示例 3:
输入: " 3+5 / 2 "
输出: 5

说明：
	你可以假设所给定的表达式都是有效的。
	请不要使用内置的库函数 eval。
*/

// https://leetcode.com/problems/basic-calculator-ii/discuss/63006/C%2B%2B-stack-solution.
// 抄的
int calculate(string expr)
{
	// 相当于 expr 前面再有个 +
	char c = '+';
	int y = 0, x = 0;
	vector<int> num;
	// 不用判断是不是最后一个，因为可能只有一个数字
	expr.push_back('+');

	for (char e : expr)
	{
		if (isspace(e))
			continue;
		if (isdigit(e))
			x = x * 10 + (e - '0');
		else
		{
			if (c == '+')
				num.push_back(x);
			else if (c == '-')
				num.push_back(-x);
			else if (c == '*')
				num.back() *= x;
			else
				num.back() /= x;
			c = e;
			x = 0;
		}
	}

	while (!num.empty())
	{
		y += num.back();
		num.pop_back();
	}
	return y;
}


int main()
{
	OutExpr(calculate("3+2*2"), "%d");
	OutExpr(calculate(" 3/2 "), "%d");
	OutExpr(calculate(" 3+5 / 2 "), "%d");
}
