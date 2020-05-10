#include "leetcode.hpp"

/* 7. 整数反转

给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。

示例 1:
输入: 123
输出: 321

示例 2:
输入: -123
输出: -321

示例 3:
输入: 120
输出: 21

注意:
假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−2^31,  2^31 − 1]。
请根据这个假设，如果反转后整数溢出那么就返回 0。
*/

int reverse(int x)
{
	bool b = x < 0;
	int y = 0, d, z;
	// C++17 规定整数除法商向 0 截断
	for (x = abs(x); x;)
	{
		d = x % 10;
		x /= 10;
		z = y * 10U + d;
		if ((z - d) / 10 != y)
			return 0;
		y = z;
	}
	return b ? -y : y;
}


int main()
{
	OutExpr(reverse(123), "%d");
	OutExpr(reverse(-123), "%d");
	OutExpr(reverse(120), "%d");
	OutExpr(reverse(1534236469), "%d");
	OutExpr(reverse(INT_MAX), "%d");
}
