#include "leetcode.hpp"

/* 813. 最大平均值和的分组

我们将给定的数组 A 分成 K 个相邻的非空子数组，我们的分数由每个子数组内的平均值的总和构成。
计算我们所能得到的最大分数是多少。

注意我们必须使用 A 数组中的每一个数进行分组，并且分数不一定需要是整数。

示例:
输入:
A = [9,1,2,3,9]
K = 3
输出: 20
解释:
A 的最优分组是[9], [1, 2, 3], [9]. 得到的分数是 9 + (1 + 2 + 3) / 3 + 9 = 20.
我们也可以把 A 分成[9, 1], [2], [3, 9].
这样的分组得到的分数为 5 + 2 + 6 = 13, 但不是最大值.

说明:
	1 <= A.length <= 100.
	1 <= A[i] <= 10000.
	1 <= K <= A.length.
	答案误差在 10^-6 内被视为是正确的。
*/

class Solution
{
	vector<int> A;
	double memo[128][128];

	double M(int n, int k)
	{
		if (memo[n][k] > 0)
			return memo[n][k];
		if (n < k)
			return 0;
		double cur = 0, m = 0;
		for (int i = n - 1; i > 0; --i)
		{
			cur += A[i];
			m = std::max(m, M(i, k - 1) + cur / (n - i));
		}
		memo[n][k] = m;
		return m;
	}

public:
	// https://leetcode.com/problems/largest-sum-of-averages/discuss/122739/C%2B%2BJavaPython-Easy-Understood-Solution-with-Explanation
	double largestSumOfAverages1(vector<int>& ary, int K)
	{
		A.swap(ary);
		memset(memo, 0, sizeof(memo));
		int len = static_cast<int>(A.size());
		double cur = 0;
		for (int i = 0; i < len; ++i)
		{
			cur += A[i];
			memo[i + 1][1] = cur / (i + 1);
		}
		return M(len, K);
	}

	// https://leetcode-cn.com/problems/largest-sum-of-averages/solution/zui-da-ping-jun-zhi-he-de-fen-zu-by-leetcode/
	double largestSumOfAverages(vector<int>& ary, int K)
	{
		A.swap(ary);
		memset(memo, 0, sizeof(memo[0]));
		double *P = memo[0], *dp = memo[1];
		int len = static_cast<int>(A.size());

		for (int i = 0; i < len; ++i)
			P[i + 1] = P[i] + A[i];
		for (int i = 0; i < len; ++i)
			dp[i] = (P[len] - P[i]) / (len - i);

		for (; --K;)
			for (int i = 0; i < len; ++i)
				for (int q = i + 1; q < len; ++q)
				{
					dp[i] = std::max(dp[i],
						(P[q] - P[i]) / (q - i) + dp[q]);
				}

		return dp[0];
	}
};

int main()
{
	vector<int>
		A0 = { 9, 1, 2, 3, 9 };
	Solution s;
	OutExpr(s.largestSumOfAverages(A0, 3), "%f");
}
