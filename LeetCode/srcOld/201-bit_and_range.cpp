#include "leetcode.hpp"

/* 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647
 * 返回此范围内所有数字的按位与（包含 m, n 两端点）*/

// 超时
int rangeBitwiseAnd1(int m, int n)
{
	int ans = n;
	for (; (m < n) && ans; ++m)
		ans &= m;
	return ans;
}


/* Consider the bits from low to high
 * if n > m, the lowest bit will be 0, and then we could transfer the problem to sub-problem:
 * rangeBitwiseAnd(m >> 1, n >> 1) */
int rangeBitwiseAnd2(int m, int n)
{
	unsigned mask = -1; // 0xffffffff;
	for (; (m & mask) != (n & mask); mask <<= 1)
		;
	return static_cast<int>(m & mask);
}


int rangeBitwiseAnd3(int m, int n)
{
	int shift = 0;
	while (m != n)
	{
		m >>= 1; n >>= 1;
		++shift;
	}
	return m << shift;
}


int main()
{
	int ans1 = rangeBitwiseAnd1(10, 11);
	int ans2 = rangeBitwiseAnd2(10, 11);
	int ans3 = rangeBitwiseAnd3(10, 11);
	printf("%1s: %d, %d, %d\n",
		"rangeBitwiseAnd", ans1, ans2, ans3);
}
