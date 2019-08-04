#include "leetcode.hpp"

/* 313. Super Ugly Number
 * Write a program to find the nth super ugly number.
 * Super ugly numbers are positive numbers,
 * whose all prime factors are in the given prime list primes of size k.
 */

 // https://leetcode.com/problems/super-ugly-number/discuss/76291/Java-three-methods-23ms-36-ms-58ms(with-heap)-performance-explained
 // 抄的
int nthSuperUglyNumber(int n, vector<int>& primes)
{
	int const len = static_cast<int>(primes.size());
	vector<int> ugly; ugly.reserve(n);
	vector<int> idx(len, 0);
	vector<int> vals(len, 1);
	int cur = 1;
	ugly.push_back(1);

	while (--n)
	{
		cur = INT_MAX;
		for (int i = 0; i < len; ++i)
		{
			// 上一次使用它更新的
			if (vals[i] == ugly.back())
			{
				vals[i] = ugly[idx[i]] * primes[i];
				++(idx[i]);
			}
			cur = std::min(cur, vals[i]);
		}
		ugly.push_back(cur);
	}

	return ugly.back();
}


int main()
{
	vector<int> nums = { 2, 7, 13, 19 };
	int n = 12;
	int ans = nthSuperUglyNumber(n, nums);
	printf("nthSuperUglyNumber (%d): %d\n", n, ans);
}

