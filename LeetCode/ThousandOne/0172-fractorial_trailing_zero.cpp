#include "leetcode.hpp"

/* 172. 阶乘后的零

给定一个整数 n，返回 n! 结果尾数中零的数量。

示例 1:
输入: 3
输出: 0
解释: 3! = 6, 尾数中没有零。

示例 2:
输入: 5
输出: 1
解释: 5! = 120, 尾数中有 1 个零.

说明: 你算法的时间复杂度应为 O(log n) 。
*/

// https://leetcode-cn.com/problems/factorial-trailing-zeroes/solution/jie-cheng-hou-de-ling-by-leetcode/
// 抄的
int trailingZeroes(int n)
{
	int a = 0;
	while (n >= 5)
	{
		n /= 5;
		a += n;
	}
	return a;
}


int main()
{
	OutExpr(trailingZeroes(3), "%d");
	OutExpr(trailingZeroes(5), "%d");
	OutExpr(trailingZeroes(200), "%d");
}
