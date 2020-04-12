#include "leetcode.hpp"

/* 1201. 丑数 III

请你帮忙设计一个程序，用来找出第 n 个丑数。

丑数是可以被 a 或 b 或 c 整除的 正整数。

示例 1：
输入：n = 3, a = 2, b = 3, c = 5
输出：4
解释：丑数序列为 2, 3, 4, 5, 6, 8, 9, 10... 其中第 3 个是 4。

示例 2：
输入：n = 4, a = 2, b = 3, c = 4
输出：6
解释：丑数序列为 2, 3, 4, 6, 8, 9, 12... 其中第 4 个是 6。

示例 3：
输入：n = 5, a = 2, b = 11, c = 13
输出：10
解释：丑数序列为 2, 4, 6, 8, 10, 11, 12, 13... 其中第 5 个是 10。

示例 4：
输入：n = 1000000000, a = 2, b = 217983653, c = 336916467
输出：1999999984

提示：
	1 <= n, a, b, c <= 10^9
	1 <= a * b * c <= 10^18
	本题结果在 [1, 2 * 10^9] 的范围内
*/


// https://leetcode.com/problems/ugly-number-iii/discuss/387780/C%2B%2B-Java-Binary-Search-with-Venn-Diagram-Explain-Math-Formula
// 抄的
class Solution
{
	int64_t lcm(int64_t a, int64_t b)
	{
		int64_t x = a, y = b, t;
		while (y)
		{
			t = x % y;
			x = y;
			y = t;
		}
		return a * b / x;
	}


public:
	int nthUglyNumber(int n, int a, int b, int c)
	{
		int64_t A = a, B = b, C = c, N = n;
		int64_t AB = lcm(A, B), AC = lcm(A, C), BC = lcm(B, C);
		int64_t ABC = lcm(AB, C);
		int64_t L = 1, R = INT_MAX, M, K;
		while (L < R)
		{
			M = (L + R) / 2;
			K = M / A + M / B + M / C;
			K -= M / AB + M / AC + M / BC;
			K += M / ABC;
			if (K >= N)
				R = M;
			else
				L = M + 1;
		}
		return static_cast<int>(L);
	}
};


int main()
{
	Solution s;
	OutExpr(s.nthUglyNumber(3, 2, 3, 5), "%d");
	OutExpr(s.nthUglyNumber(4, 2, 3, 4), "%d");
	OutExpr(s.nthUglyNumber(5, 2, 11, 13), "%d");
	OutExpr(s.nthUglyNumber(1000000000, 2, 217983653, 336916467), "%d");
}
