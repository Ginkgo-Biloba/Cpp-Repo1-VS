#include "leetcode.hpp"

/* 400. 第N个数字

在无限的整数序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...中找到第 n 个数字。
注意:
n 是正数且在32为整形范围内 ( n < 231)。

示例 1:
输入:
3
输出:
3

示例 2:
输入:
11
输出:
0
说明:
第11个数字在序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是0，它是10的一部分。
*/

// https://leetcode.com/problems/nth-digit/discuss/88363/Java-solution
// 抄的
int findNthDigit(int _n)
{
	int64_t n = _n;
	int64_t base = 9, digit = 1, num = 1;
	while (n > base*digit)
	{
		n -= base*digit;
		base *= 10;
		++digit;
		num *= 10;
	}

	num += (n - 1) / digit;
	int64_t idx = (n - 1) % digit;
	for (++idx; idx < digit; ++idx)
		num /= 10;
	n = num % 10;
	return static_cast<int>(n);
}


int main()
{
	OutExpr(findNthDigit(1111), "%d");
};

