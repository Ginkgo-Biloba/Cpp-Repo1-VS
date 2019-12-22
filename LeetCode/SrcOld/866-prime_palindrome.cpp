#include "leetcode.hpp"

/* 866. 回文素数

求出大于或等于 N 的最小回文素数。

回顾一下，如果一个数大于 1，且其因数只有 1 和它自身，那么这个数是素数。

例如，2，3，5，7，11 以及 13 是素数。

回顾一下，如果一个数从左往右读与从右往左读是一样的，那么这个数是回文数。

例如，12321 是回文数。

示例 1：
输入：6
输出：7

示例 2：
输入：8
输出：11

示例 3：
输入：13
输出：101

提示：
	1 <= N <= 10^8
	答案肯定存在，且小于 2 * 10^8。
*/

bool isPrime(int n)
{
	if (n < 2 || (n % 2 == 0))
		return n == 2;
	for (int i = 3; i * i <= n; i += 2)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

int primePalindrome(int N)
{
	char buf[48];
	if (8 <= N && N <= 11)
		return 11;
	for (int x = 1; x < 100000; ++x)
	{
		sprintf(buf, "%d", x);
		int len = static_cast<int>(strlen(buf));
		for (int i = len - 2; i >= 0; --i)
			buf[2 * len - i - 2] = buf[i];
		buf[2 * len - 1] = '\0';
		int y = atoi(buf);
		if (y >= N && isPrime(y))
			return y;
	}
	return -1;
}


int main()
{
	OutExpr(primePalindrome(6), "%d");
	OutExpr(primePalindrome(8), "%d");
	OutExpr(primePalindrome(13), "%d");
}
