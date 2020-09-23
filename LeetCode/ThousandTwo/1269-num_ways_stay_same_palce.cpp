#include "leetcode.hpp"

/* 1269. 停在原地的方案数

有一个长度为 arrLen 的数组，开始有一个指针在索引 0 处。

每一步操作中，你可以将指针向左或向右移动 1 步，或者停在原地（指针不能被移动到数组范围外）。

给你两个整数 steps 和 arrLen ，请你计算并返回：在恰好执行 steps 次操作以后，指针仍然指向索引 0 处的方案数。

由于答案可能会很大，请返回方案数 模 10^9 + 7 后的结果。

示例 1：
输入：steps = 3, arrLen = 2
输出：4
解释：3 步后，总共有 4 种不同的方法可以停在索引 0 处。
向右，向左，不动
不动，向右，向左
向右，不动，向左
不动，不动，不动

示例  2：
输入：steps = 2, arrLen = 4
输出：2
解释：2 步后，总共有 2 种不同的方法可以停在索引 0 处。
向右，向左
不动，不动

示例 3：
输入：steps = 4, arrLen = 2
输出：8

提示：
	1 <= steps <= 500
	1 <= arrLen <= 10^6
*/


int numWays(int steps, int arrLen)
{
	unsigned const Mod = 1e9 + 7;
	// 至少 2 个，这样不用右边界判断
	unsigned limit = min(steps / 2 + 2, arrLen);
	if (arrLen == 1)
		return 1;
	vector<unsigned> A(limit), B(limit);
	A[0] = 1;
	for (int s = 0; s < steps; ++s)
	{
		B[0] = (A[0] + A[1]) % Mod;
		B[limit - 1] = (A[limit - 1] + A[limit - 2]) % Mod;
		for (unsigned i = 1; i != limit - 1; ++i)
			B[i] = (A[i - 1] + A[i] + A[i + 1]) % Mod;
		B.swap(A);
	}
	return A[0];
}


int main()
{
	OutExpr(numWays(3, 2), "%d");
	OutExpr(numWays(2, 4), "%d");
	OutExpr(numWays(4, 2), "%d");
}
