#include "leetcode.hpp"

/* 829. 连续整数求和

给定一个正整数 N，试求有多少组连续正整数满足所有数字之和为 N?

示例 1:
输入: 5
输出: 2
解释: 5 = 5 = 2 + 3，共有两组连续整数([5],[2,3])求和后为 5。

示例 2:
输入: 9
输出: 3
解释: 9 = 9 = 4 + 5 = 2 + 3 + 4

示例 3:
输入: 15
输出: 4
解释: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5

说明: 1 <= N <= 10^9
*/

/*
\sum_{x}_{k}(x+k) = N
kx = N - (k*(K-1))/2
*/
int consecutiveNumbersSum(int N)
{
	int ans = 1;
	int up = static_cast<int>(sqrt(2.0*N));
	for (int k = 2; k <= up; ++k)
	{
		int r = N - k * (k - 1) / 2;
		if ((r > 0) && (r % k == 0))
			++ans;
	}
	return ans;
}


int main()
{
	OutExpr(consecutiveNumbersSum(5), "%d");
	OutExpr(consecutiveNumbersSum(9), "%d");
	OutExpr(consecutiveNumbersSum(15), "%d");
}
