#include "leetcode.hpp"

/* 738. 单调递增的数字

给定一个非负整数 N，找出小于或等于 N 的最大的整数，同时这个整数需要满足其各个位数上的数字是单调递增，当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。

示例 1:
输入: N = 10
输出: 9

示例 2:
输入: N = 1234
输出: 1234

示例 3:
输入: N = 332
输出: 299

说明: N 是在 [0, 10^9] 范围内的一个整数。
*/

// https://leetcode.com/problems/monotone-increasing-digits/discuss/109794/Simple-Python-solution-w-Explanation
// 抄的
int monotoneIncreasingDigits(int N)
{
	int bits[16], len = 0;
	int idx = -1, n = N;

	while (N)
	{
		bits[len] = N % 10;
		N = N / 10;
		++len;
	}

	for (int i = 1; i < len; ++i)
	{
		if ((bits[i] > bits[i - 1])
			|| (idx > 0 && bits[idx] == bits[i]))
			idx = i;
	}

	if (idx < 0)
		return N;
	for (int i = 0; i < idx; ++i)
		bits[i] = 9;
	if (idx > 0)
		bits[idx] -= 1;

	for (int i = len - 1; i >= 0; --i)
		N = N * 10 + bits[i];

	return N;
}


int main()
{
	OutExpr(monotoneIncreasingDigits(10), "%d");
	OutExpr(monotoneIncreasingDigits(1234), "%d");
	OutExpr(monotoneIncreasingDigits(332), "%d");
}
