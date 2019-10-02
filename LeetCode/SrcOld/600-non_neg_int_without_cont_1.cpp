#include "leetcode.hpp"

/* 600. 不含连续1的非负整数

给定一个正整数 n，找出小于或等于 n 的非负整数中，其二进制表示不包含 连续的1 的个数。

示例 1:
输入: 5
输出: 5
解释:
下面是带有相应二进制表示的非负整数<= 5：
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
其中，只有整数3违反规则（有两个连续的1），其他5个满足规则。

说明: 1 <= n <= 10^9
*/

// https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/solution/bu-han-lian-xu-1de-fei-fu-zheng-shu-by-leetcode/
// 抄的答案
int findIntegers(int num)
{
	int fb[32] = { 1, 2 };
	int b = 2, sum = 0, prev = 0;
	for (; b < 32; ++b)
		fb[b] = fb[b - 1] + fb[b - 2];

	for (b = 30; b >= 0; --b)
	{
		if (num & (1 << b))
		{
			sum += fb[b];
			if (prev)
				return sum;
			prev = 1;
		}
		else
			prev = 0;
	}

	return sum + 1;
}


int main()
{
	OutExpr(findIntegers(5), "%d");
}
