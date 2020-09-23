#include "leetcode.hpp"

/* 793. 阶乘函数后K个零

f(x) 是 x! 末尾是0的数量。（回想一下 x! = 1 * 2 * 3 * ... * x，且0! = 1）

例如， f(3) = 0 ，因为3! = 6的末尾没有0；而 f(11) = 2 ，因为11!= 39916800末端有2个0。
给定 K，找出多少个非负整数x ，有 f(x) = K 的性质。

示例 1:
输入:K = 0
输出:5
解释: 0!, 1!, 2!, 3!, and 4! 均符合 K = 0 的条件。

示例 2:
输入:K = 5
输出:0
解释:没有匹配到这样的 x!，符合K = 5 的条件。

注意：
	K是范围在 [0, 10^9] 的整数。
*/

// https://leetcode-cn.com/problems/preimage-size-of-factorial-zeroes-function/solution/kuai-su-cha-zhao-zui-ke-neng-de-jie-guo-by-xinzhao/
// 抄的

int zeroNum(int64_t n)
{
	int cnt = 0;
	while (n)
	{
		n /= 5;
		cnt += static_cast<int>(n);
	}
	return cnt;
}

int preimageSizeFZF(int K)
{
	int64_t L = INT64_C(4) * K, R = L + K;
	int cnt = 0;
	while (L <= R)
	{
		int64_t M = (L + R) >> 1;
		cnt = zeroNum(M);
		if (cnt == K)
			return 5;
		else if (cnt < K)
			L = M + 1;
		else
			R = M - 1;
	}
	return 0;
}

int main()
{
	OutExpr(preimageSizeFZF(0), "%d");
	OutExpr(preimageSizeFZF(2), "%d");
}
