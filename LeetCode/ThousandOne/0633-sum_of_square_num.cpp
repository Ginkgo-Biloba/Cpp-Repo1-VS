#include "leetcode.hpp"

/* 633. 平方数之和

给定一个非负整数 c ，你要判断是否存在两个整数 a 和 b，使得 a2 + b2 = c。

示例1:
输入: 5
输出: True
解释: 1 * 1 + 2 * 2 = 5

示例2:
输入: 3
输出: False
*/

bool judgeSquareSum(int c)
{
	int lo = static_cast<int>(::sqrt(c / 2));
	int hi = static_cast<int>(::sqrt(c)) + 1;
	for (int b = lo; b < hi; ++b)
	{
		int a = c - b * b;
		int r = static_cast<int>(::sqrt(a));
		if (r * r == a)
			return true;
	}
	return false;
}


int main()
{
	OutExpr(boolstr[judgeSquareSum(7)], "%s");
}
