#include "leetcode.hpp"

/* 50. Pow(x, n)

实现 pow(x, n) ，即计算 x 的 n 次幂函数。

示例 1:
输入: 2.00000, 10
输出: 1024.00000

示例 2:
输入: 2.10000, 3
输出: 9.26100

示例 3:
输入: 2.00000, -2
输出: 0.25000
解释: 2-2 = 1/22 = 1/4 = 0.25

说明:
	-100.0 < x < 100.0
	n 是 32 位有符号整数，其数值范围是 [−2^31, 2^31 − 1] 。
*/

double myPow(double x, int n)
{
	unsigned m = abs(n);
	double y = 1, b = x;
	for (; m; m >>= 1)
	{
		if (m & 1)
			y *= b;
		b *= b;
	}
	if (n < 0)
		y = 1.0 / y;
	return y;
}

int main()
{
	OutExpr(myPow(2.0, 10), "%f");
	OutExpr(myPow(2.1, 3), "%f");
	OutExpr(myPow(2.0, -2), "%f");
}
