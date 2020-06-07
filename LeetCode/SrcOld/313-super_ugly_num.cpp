#include "leetcode.hpp"

/* 313. 超级丑数

编写一段程序来查找第 n 个超级丑数。

超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。

示例:

输入: n = 12, primes = [2,7,13,19]
输出: 32
解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。

说明:
	1 是任何给定 primes 的超级丑数。
	给定 primes 中的数字以升序排列。
	0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000 。
	第 n 个超级丑数确保在 32 位有符整数范围内。
*/

// https://leetcode.com/problems/super-ugly-number/discuss/169815/Python-DP-solution-beats-93.7-extremely-detailed-explanation
// 抄的
int nthSuperUglyNumber(int n, vector<int>& primes)
{
	int k = static_cast<int>(primes.size());
	vector<int> cand(k, 1), idx(k, 0);
	vector<int> ugly = { 1 };
	while (--n)
	{
		int cur = INT_MAX;
		for (int i = 0; i < k; ++i)
		{
			// 上一次用的是它
			if (cand[i] == ugly.back())
			{
				cand[i] = ugly[idx[i]] * primes[i];
				idx[i] += 1;
			}
			cur = min(cur, cand[i]);
		}
		ugly.push_back(cur);
	}
	return ugly.back();
}


int main()
{
	vector<int> a = { 2, 7, 13, 19 };
	OutExpr(nthSuperUglyNumber(12, a), "%d");
}
