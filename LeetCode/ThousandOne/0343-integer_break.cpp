#include "leetcode.hpp"

/* 343. 整数拆分

给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。
返回你可以获得的最大乘积。

示例 1:
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。

示例 2:
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。

说明: 你可以假设 n 不小于 2 且不大于 58。
*/

// https://leetcode-cn.com/problems/integer-break/solution/343-zheng-shu-chai-fen-tan-xin-by-jyd/
// 抄的
int pow3(int n)
{
	int p = 1;
	for (; n > 0; --n)
		p *= 3;
	return p;
}

int integerBreak(int n)
{
	if (n <= 3)
		return n - 1;
	int a = n / 3, b = n % 3;
	if (b == 0)
		return pow3(a);
	if (b == 1)
		return pow3(a - 1) * 4;
	return pow3(a) * 2;
}


int main()
{
	OutExpr(integerBreak(10), "%d");
}
