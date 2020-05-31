#include "leetcode.hpp"

/* 264. 丑数 II

编写一个程序，找出第 n 个丑数。

丑数就是质因数只包含 2, 3, 5 的正整数。

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。

说明:
	1 是丑数。
	n 不超过1690。
*/

// https://leetcode.com/problems/ugly-number-ii/discuss/69364/My-16ms-C%2B%2B-DP-solution-with-short-explanation
// 抄的
int nthUglyNumber(int n)
{
	if (n < 3)
		return n;
	vector<int> k(n);
	int i2 = 0, i3 = 0, i5 = 0;
	k[0] = 1;
	for (int i = 1; i < n; ++i)
	{
		int a = k[i2] * 2;
		int b = k[i3] * 3;
		int c = k[i5] * 5;
		k[i] = min(min(a, b), c);
		if (k[i] == a) ++i2;
		if (k[i] == b) ++i3;
		if (k[i] == c) ++i5;
	}
	return k[n - 1];
}


int main()
{
	OutExpr(nthUglyNumber(10), "%d");
	OutExpr(nthUglyNumber(1), "%d");
}
