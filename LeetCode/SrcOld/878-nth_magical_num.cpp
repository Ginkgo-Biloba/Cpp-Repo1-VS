#include "leetcode.hpp"

/* 878. 第 N 个神奇数字

如果正整数可以被 A 或 B 整除，那么它是神奇的。

返回第 N 个神奇数字。
由于答案可能非常大，返回它模 10^9 + 7 的结果。

示例 1：
输入：N = 1, A = 2, B = 3
输出：2

示例 2：
输入：N = 4, A = 2, B = 3
输出：6

示例 3：
输入：N = 5, A = 2, B = 4
输出：10

示例 4：
输入：N = 3, A = 6, B = 4
输出：8

提示：
	1 <= N <= 10^9
	2 <= A <= 40000
	2 <= B <= 40000
*/

int64_t lcm(int A, int B)
{
	int a = A, b = B;
	int t = a % b;
	while (t)
	{
		a = b;
		b = t;
		t = a % b;
	}
	return static_cast<int64_t>(A / b) * B;
}

int nthMagicalNumber(int N, int A, int B)
{
	int64_t const Mod = 1e9 + 7;
	int64_t C = lcm(A, B);
	int64_t M, S, L = 2;
	int64_t R = static_cast<int64_t>(N) * std::min(A, B);
	while (L < R)
	{
		M = (L + R) / 2;
		S = M / A + M / B - M / C;
		if (S < N)
			L = M + 1;
		else
			R = M;
	}
	return static_cast<int>(L % Mod);
}


int main()
{
	OutExpr(nthMagicalNumber(1, 2, 3), "%d");
	OutExpr(nthMagicalNumber(4, 2, 3), "%d");
	OutExpr(nthMagicalNumber(5, 2, 4), "%d");
	OutExpr(nthMagicalNumber(3, 6, 4), "%d");
}
