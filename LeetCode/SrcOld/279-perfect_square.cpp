#include "leetcode.hpp"

/* 279. 完全平方数

给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。
你需要让组成和的完全平方数的个数最少。

示例 1:
输入: n = 12
输出: 3
解释: 12 = 4 + 4 + 4.

示例 2:
输入: n = 13
输出: 2
解释: 13 = 4 + 9.
*/

// https://leetcode.com/problems/perfect-squares/discuss/71618/4ms-C%2B%2B-code-Solve-it-mathematically
// 抄的
int numSquares_1(int n)
{
	while ((n & 3) == 0)
		n >>= 2;
	if ((n & 7) == 7)
		return 4;
	int r = static_cast<int>(sqrt(n));
	if (r * r == n)
		return 1;
	for (int i = 1; i <= r; ++i)
	{
		int k = n - i * i;
		int m = static_cast<int>(sqrt(k));
		if (m * m == k)
			return 2;
	}
	return 3;
}

// https://leetcode.com/problems/perfect-squares/discuss/71533/O(sqrt(n))-in-Ruby-C%2B%2B-C
// 抄的
int numSquares(int n)
{
	int r = static_cast<int>(sqrt(n));
	for (int a = 0; a <= r; ++a)
		for (int b = a; b <= r; ++b)
		{
			int k = n - a * a - b * b;
			if (k < 0) break;
			int c = static_cast<int>(sqrt(k));
			if (c * c == k)
				return !!a + !!b + !!c;
		}
	return 4;
}


int main()
{
	for (int i = 1; i <= 40; ++i)
	{
		printf("%3d:%-3d  ", i, numSquares(i));
		if ((i & 7) == 0)
			puts("");
	}
	puts("");
}
