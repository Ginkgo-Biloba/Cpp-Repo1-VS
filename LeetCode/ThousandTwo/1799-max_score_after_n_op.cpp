#include "leetcode.hpp"

/* 1799. N 次操作后的最大分数和

给你 nums ，它是一个大小为 2 * n 的正整数数组。
你必须对这个数组执行 n 次操作。

在第 i 次操作时（操作编号从 1 开始），你需要：
	选择两个元素 x 和 y 。
	获得分数 i * gcd(x, y) 。
	将 x 和 y 从 nums 中删除。

请你返回 n 次操作后你能获得的分数和最大为多少。

函数 gcd(x, y) 是 x 和 y 的最大公约数。

示例 1：
输入：nums = [1,2]
输出：1
解释：最优操作是：
(1 * gcd(1, 2)) = 1

示例 2：
输入：nums = [3,4,6,8]
输出：11
解释：最优操作是：
(1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11

示例 3：
输入：nums = [1,2,3,4,5,6]
输出：14
解释：最优操作是：
(1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14

提示：
	1 <= n <= 7
	nums.length == 2 * n
	1 <= nums[i] <= 10^6
*/

// https://leetcode.com/problems/maximize-score-after-n-operations/discuss/1118778/C%2B%2BJavaPython-Bitmask-DP
// 抄的
class Solution
{
	vector<array<int, 16384>> dp;
	vector<int> A;
	int len;

	int gcd(int a, int b)
	{
		int t = a % b;
		while (t)
		{
			a = b;
			b = t;
			t = a % b;
		}
		return b;
	}

	int dfs(int i, int m)
	{
		if (i * 2 > len)
			return 0;
		if (dp[i][m])
			return dp[i][m];
		for (int j = 0; j < len; ++j)
			for (int k = j + 1; k < len; ++k)
			{
				int mask = (1 << j) | (1 << k);
				if (!(m & mask))
					dp[i][m] = max(dp[i][m],
						i * gcd(A[j], A[k]) + dfs(i + 1, m | mask));
			}
		return dp[i][m];
	}

public:
	int maxScore(vector<int>& nums)
	{
		A = nums;
		len = static_cast<int>(A.size());
		dp.resize(8);
		memset(dp.data(), 0, dp.size() * sizeof(dp[0]));
		dfs(1, 0);
		return dp[1][0];
	}
};


int main()
{
	vector<int>
		a = { 1, 2 },
		b = { 3, 4, 6, 8 },
		c = { 1, 2, 3, 4, 5, 6 };
	Solution s;
	OutExpr(s.maxScore(a), "%d");
	OutExpr(s.maxScore(b), "%d");
	OutExpr(s.maxScore(c), "%d");
}
