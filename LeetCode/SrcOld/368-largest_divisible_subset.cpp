#include "leetcode.hpp"

/* 368. 最大整除子集

给出一个由无重复的正整数组成的集合，找出其中最大的整除子集，子集中任意一对 (Si，Sj) 都要满足：Si % Sj = 0 或 Sj % Si = 0。

如果有多个目标子集，返回其中任何一个均可。

示例 1:
输入: [1,2,3]
输出: [1,2] (当然, [1,3] 也正确)

示例 2:
输入: [1,2,4,8]
输出: [1,2,4,8]
*/

// https://leetcode.com/problems/largest-divisible-subset/discuss/83998/C%2B%2B-Solution-with-Explanations
// 抄的
vector<int> largestDivisibleSubset(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int dst = 0, step = 0;
	sort(A.begin(), A.end());
	vector<int> dp(len), par(len), ans;

	for (int i = len - 1; i >= 0; --i)
		for (int h = i; h < len; ++h)
			if (A[h] % A[i] == 0 && dp[i] <= dp[h])
			{
				dp[i] = 1 + dp[h];
				par[i] = h;
				if (dp[i] > step)
				{
					step = dp[i];
					dst = i;
				}
			}

	for (int i = 0; i < step; ++i)
	{
		ans.push_back(A[dst]);
		dst = par[dst];
	}
	return ans;
}


int main()
{}
