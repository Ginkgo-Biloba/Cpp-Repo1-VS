#include "leetcode.hpp"

/* 233. 数字 1 的个数

给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。

示例:

输入: 13
输出: 6
解释: 数字 1 出现在以下数字中: 1, 10, 11, 12, 13 。
*/

// https://leetcode.com/problems/number-of-digit-one/discuss/64381/4%2B-lines-O(log-n)-C%2B%2BJavaPython
// 抄的
int countDigitOne(int n)
{
	int64_t s = 0;
	for (int64_t m = 1; m <= n; m *= 10)
	{
		int64_t a = n / m;
		int64_t b = n % m;
		s += (a + 8) / 10 * m;
		s += (a % 10 == 1) * (b + 1);
	}
	return static_cast<int>(s);
}


int main()
{
	OutExpr(countDigitOne(13), "%d");
	OutExpr(countDigitOne(999), "%d");
}
