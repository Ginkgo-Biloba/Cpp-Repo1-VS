#include "leetcode.hpp"

/* 201. 数字范围按位与

给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

示例 1:
输入: [5,7]
输出: 4

示例 2:
输入: [0,1]
输出: 0
*/

int rangeBitwiseAnd(int m, int n)
{
	int r = 0, s = 1 << 30;
	while (s && ((s & m) == (s & n)))
	{
		r |= (s & m);
		s >>= 1;
	}
	return r;
}

int main()
{
	OutExpr(rangeBitwiseAnd(5, 7), "%d");
	OutExpr(rangeBitwiseAnd(0, 1), "%d");
	OutExpr(rangeBitwiseAnd(2334, 5464), "%d");
}
