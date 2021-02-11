#include "leetcode.hpp"

/* 1735. 生成乘积数组的方案数

给你一个二维整数数组 queries ，其中 queries[i] = [ni, ki] 。
第 i 个查询 queries[i] 要求构造长度为 ni 、每个元素都是正整数的数组，且满足所有元素的乘积为 ki ，请你找出有多少种可行的方案。
由于答案可能会很大，方案数需要对 10^9 + 7 取余 。

请你返回一个整数数组 answer，满足 answer.length == queries.length ，其中 answer[i]是第 i 个查询的结果。

示例 1：

输入：queries = [[2,6],[5,1],[73,660]]
输出：[4,1,50734910]
解释：每个查询之间彼此独立。
[2,6]：总共有 4 种方案得到长度为 2 且乘积为 6 的数组：[1,6]，[2,3]，[3,2]，[6,1]。
[5,1]：总共有 1 种方案得到长度为 5 且乘积为 1 的数组：[1,1,1,1,1]。
[73,660]：总共有 1050734917 种方案得到长度为 73 且乘积为 660 的数组。1050734917 对 109 + 7 取余得到 50734910 。

示例 2 ：

输入：queries = [[1,1],[2,2],[3,3],[4,4],[5,5]]
输出：[1,2,3,10,5]

提示：
	1 <= queries.length <= 10^4
	1 <= ni, ki <= 10^4
*/

// https://leetcode.com/problems/count-ways-to-make-array-with-product/discuss/1035607/C%2B%2B-Precompute
// 抄的
vector<int> waysToFillArray(vector<vector<int>>& queries)
{
	/// 质数表
	vector<int> primes;
	for (int i = 2; i < 102; ++i)
	{
		int u = static_cast<int>(::sqrt(i));
		for (; u >= 2; --u)
		{
			if (i % u == 0)
				break;
		}
		if (u < 2)
			primes.push_back(i);
	}

	/// 隔板法 stars and bars
	vector<array<int64_t, 14>> dp(10013);
	int64_t const mod = static_cast<int64_t>(1e9 + 7);
	memset(dp[0].data(), 0, sizeof(dp[0]));
	dp[0][0] = 1;
	for (int n = 1; n < 10013; ++n)
	{
		dp[n][0] = 1;
		for (int r = 1; r < 14; ++r)
			dp[n][r] = (dp[n - 1][r - 1] + dp[n - 1][r]) % mod;
	}

	/// 计数
	vector<int> ans;
	for (auto const& q : queries)
	{
		int64_t d = 1;
		int n = q[0], k = q[1];
		for (auto p : primes)
		{
			int r = 0;
			while (k % p == 0)
			{
				++r;
				k /= p;
			}
			d = (d * dp[n + r - 1][r]) % mod;
		}
		if (k != 1)
			d = (d * dp[n][1]) % mod;
		ans.push_back(static_cast<int>(d));
	}

	return ans;
}


int main()
{
	vector<vector<int>>
		a = { { 2, 6 }, { 5, 1 }, { 73, 660 } },
		b = { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 } };
	output(waysToFillArray(a), "make array with product");
	output(waysToFillArray(b), "make array with product");
}
