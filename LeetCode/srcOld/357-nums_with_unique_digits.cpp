#include "leetcode.hpp"

/* 357. 计算各个位数不同的数字个数

给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10n 。

示例:
输入: 2
输出: 91
解释: 答案应为除去 11,22,33,44,55,66,77,88,99 外，在 [0,100) 区间内的所有数字。
*/

int countNumbersWithUniqueDigits(int n)
{
	if (n == 0) return 1;

	int ans = 10;
	int p = 9, left = 9;
	for (int i = 1; i < n; ++i)
	{
		p *= left; --left;
		ans += p;
	}
	return ans;
}


int main()
{
	int count = countNumbersWithUniqueDigits(2);
	printf("maxEnvelopes: %d\n", count);
}
