#include "leetcode.hpp"

/* 204. 计数质数

统计所有小于非负整数 n 的质数的数量。

示例:

输入: 10
输出: 4
解释: 小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
*/

int countPrimes(int n)
{
	if (n < 3)
		return 0;
	int istop = static_cast<int>(sqrt(n));
	int ans = 0, i = 0;
	vector<unsigned> f(n / 32 + 1);
	f[0] |= 0x3;
	for (i = 2; i <= istop; ++i)
	{
		if (f[i >> 5] & (1U << (i & 31)))
			continue;
		for (int k = i * i; k < n; k += i)
			f[k >> 5] |= (1U << (k & 31));
	}
	for (i = 0; i <= n - 32; i += 32)
		ans += 32 - _mm_popcnt_u32(f[i >> 5]);
	for (; i < n; ++i)
		ans += !(f[i >> 5] & (1U << (i & 31)));
	return ans;
}


int main()
{
	OutExpr(countPrimes(3), "%d");
	OutExpr(countPrimes(10), "%d");
	OutExpr(countPrimes(12), "%d");
}
