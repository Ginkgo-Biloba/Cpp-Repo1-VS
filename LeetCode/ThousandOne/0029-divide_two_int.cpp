#include "leetcode.hpp"

/* 29. 两数相除

给定两个整数，被除数 dividend 和除数 divisor。
将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

示例 1:
输入: dividend = 10, divisor = 3
输出: 3
解释: 10/3 = truncate(3.33333..) = truncate(3) = 3

示例 2:
输入: dividend = 7, divisor = -3
输出: -2
解释: 7/-3 = truncate(-2.33333..) = -2

提示：
	被除数和除数均为 32 位有符号整数。
	除数不为 0。
	假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31,  2^31 − 1]。本题中，如果除法结果溢出，则返回 2^31 − 1。
*/

unsigned divide1(unsigned a, unsigned b)
{
	if (b == 1)
		return a;
	unsigned s = 0;
	while (a >= b)
	{
		unsigned c = b, m = 0;
		// 如果高位是 1，则不能继续左移
		while ((!(c & INT_MIN)) && ((c << 1) <= a))
		{
			c <<= 1;
			++m;
		}
		s |= (1 << m);
		a -= c;
	}
	return s;
}

int divide(int dividend, int divisor)
{
	unsigned a = abs(dividend), b = abs(divisor);
	unsigned c = divide1(a, b);
	bool neg = ((dividend ^ divisor) < 0);
	if ((c > INT_MAX) && !neg)
		return INT_MAX;
	int s = neg ? -c : c;
	return s;
}

int main()
{
	OutExpr(divide(10, 3), "%d");
	OutExpr(divide(7, -3), "%d");
	OutExpr(divide(INT_MAX, 1), "%d");
	OutExpr(divide(INT_MIN, -1), "%d");
	OutExpr(divide(INT_MIN, 1), "%d");
	OutExpr(divide(INT_MIN, -2), "%d");
}
