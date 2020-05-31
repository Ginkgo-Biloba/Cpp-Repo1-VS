#include "leetcode.hpp"

/* 224. 基本计算器

实现一个基本的计算器来计算一个简单的字符串表达式的值。

字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格。

示例 1:
输入: "1 + 1"
输出: 2

示例 2:
输入: " 2-1 + 2 "
输出: 3

示例 3:
输入: "(1+(4+5+2)-3)+(6+8)"
输出: 23

说明：
	你可以假设所给定的表达式都是有效的。
	请不要使用内置的库函数 eval。
*/

class Solution_Org
{
	vector<int> par, stk;

	int eval(char const* s, int a, int b)
	{
		int y = 0, c = '+', x;
		while (a <= b)
		{
			if (s[a] == '+' || s[a] == '-')
			{
				c = s[a];
				++a;
				continue;
			}
			x = 0;
			if (isdigit(s[a]))
			{
				for (; a <= b && isdigit(s[a]); ++a)
					x = x * 10 + (s[a] - '0');
			}
			else
			{
				assert(s[a] == '(');
				x = eval(s, a + 1, par[a] - 1);
				a = par[a] + 1;
			}
			if (c == '+')
				y += x;
			else
				y -= x;
			c = '+';
		}
		return y;
	}

public:
	int calculate(string s)
	{
		int len = static_cast<int>(s.length());
		int h = 0, i = 0;
		par.assign(len, 0);
		for (; i < len; ++i)
		{
			if (s[i] == ' ')
				continue;
			s[h] = s[i];
			if (s[i] == '(')
				stk.push_back(h);
			if (s[i] == ')')
			{
				par[stk.back()] = h;
				par[h] = stk.back();
				stk.pop_back();
			}
			++h;
		}
		for (; len > h; --len)
			s.pop_back();
		return eval(s.data(), 0, h - 1);
	}
};


class Solution
{
public:
	int calculate(string s)
	{
		int len = static_cast<int>(s.length());
		vector<int> num;
		string ops;
		int y = 0, x;
		char c = '+';
		for (int i = 0; i < len; ++i)
		{
			if (s[i] == ' ')
				;
			else if (isdigit(s[i]))
			{
				x = s[i] - '0';
				for (++i; i < len && isdigit(s[i]); ++i)
					x = x * 10 + (s[i] - '0');
				y += (c == '+' ? x : -x);
				--i;
			}
			else if (s[i] == '+' || s[i] == '-')
				c = s[i];
			else if (s[i] == '(')
			{
				num.push_back(y);
				ops.push_back(c);
				y = 0;
				c = '+';
			}
			else // s[i] == ')'
			{
				x = num.back();
				c = ops.back();
				num.pop_back();
				ops.pop_back();
				y = x + (c == '+' ? y : -y);
			}
		}
		return y;
	}
};


int main()
{
	Solution s;
	OutExpr(s.calculate(" ( 3 ) "), "%d");
	OutExpr(s.calculate("1 + 1"), "%d");
	OutExpr(s.calculate(" 2-1 + 2 "), "%d");
	OutExpr(s.calculate("(1+(4+5+2)-3)+(6+8)"), "%d");
}
