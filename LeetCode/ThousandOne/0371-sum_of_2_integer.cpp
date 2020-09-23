#include "leetcode.hpp"

/* 371. 两整数之和

不使用运算符 + 和 - ​​​​​​​，计算两整数 ​​​​​​​a 、b ​​​​​​​之和。

示例 1:
输入: a = 1, b = 2
输出: 3

示例 2:
输入: a = -2, b = 3
输出: 1
*/

int getSum(int ia, int ib)
{
	unsigned a = ia, b = ib;
	while (b)
	{
		unsigned nocarry = a ^ b;
		unsigned carry = (a & b) << 1;
		a = nocarry;
		b = carry;
	}
	return a;
}


int main()
{
	OutExpr(getSum(11, 32), "%d");
	OutExpr(getSum(-11, 32), "%d");
}
