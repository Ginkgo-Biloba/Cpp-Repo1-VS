#include "leetcode.hpp"

/* 实现 int sqrt(int x) 函数。

计算并返回 x 的平方根，其中 x 是非负整数。

由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

示例 1:
输入: 4
输出: 2

示例 2:
输入: 8
输出: 2
说明:
8 的平方根是 2.82842...,
由于返回类型是整数，小数部分将被舍去。
*/

int mySqrt_Org(int x)
{
	unsigned a = 0, c = x / 2U + 1U;
	unsigned b, s, z = x;
	// upper_bound
	while (a <= c)
	{
		b = (a + c) / 2U;
		s = b * b;
		// 没有溢出并且真的不大
		if ((b <= USHRT_MAX) && s <= z)
			a = b + 1;
		else
			c = b - 1;
	}
	return static_cast<int>(a - 1);
}


// https://leetcode.com/problems/sqrtx/discuss/25057/3-4-short-lines-Integer-Newton-Every-Language
// 抄的
int mySqrt(int x)
{
	int64_t z = x;
	int64_t r = z / 2 + 1;
	while (r * r > z)
		r = (r + z / r) / 2;
	return static_cast<int>(r);
}

int main()
{
	OutExpr(mySqrt(0), "%d");
	OutExpr(mySqrt(1), "%d");
	OutExpr(mySqrt(8), "%d");
	OutExpr(mySqrt(36), "%d");
	OutExpr(mySqrt(2147395599), "%d");
	OutExpr(mySqrt(INT_MAX), "%d");
}
