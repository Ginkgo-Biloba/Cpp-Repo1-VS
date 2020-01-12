#include "leetcode.hpp"

/* 1000. 合并石头的最低成本

有 N 堆石头排成一排，第 i 堆中有 stones[i] 块石头。

每次移动（move）需要将连续的 K 堆石头合并为一堆，而这个移动的成本为这 K 堆石头的总数。

找出把所有石头合并成一堆的最低成本。如果不可能，返回 -1 。

示例 1：
输入：stones = [3,2,4,1], K = 2
输出：20
解释：
从 [3, 2, 4, 1] 开始。
合并 [3, 2]，成本为 5，剩下 [5, 4, 1]。
合并 [4, 1]，成本为 5，剩下 [5, 5]。
合并 [5, 5]，成本为 10，剩下 [10]。
总成本 20，这是可能的最小值。

示例 2：
输入：stones = [3,2,4,1], K = 3
输出：-1
解释：任何合并操作后，都会剩下 2 堆，我们无法再进行合并。所以这项任务是不可能完成的。.

示例 3：
输入：stones = [3,5,1,2,6], K = 3
输出：25
解释：
从 [3, 5, 1, 2, 6] 开始。
合并 [5, 1, 2]，成本为 8，剩下 [3, 8, 6]。
合并 [3, 8, 6]，成本为 17，剩下 [17]。
总成本 25，这是可能的最小值。

提示：
	1 <= stones.length <= 30
	2 <= K <= 30
	1 <= stones[i] <= 100
*/


// https://leetcode.com/problems/minimum-cost-to-merge-stones/discuss/247657/JAVA-Bottom-Up-%2B-Top-Down-DP-With-Explaination
// 抄的
int mergeStones(vector<int>& stones, int K)
{
	int len = static_cast<int>(stones.size());
	int n1 = len + 1;
	if ((len - 1) % (K - 1))
		return -1;

	vector<int> acmlt(n1);
	for (int i = 0; i < len; ++i)
		acmlt[i + 1] = acmlt[i] + stones[i];

	vector<int> buf(n1 * n1 * (K + 1), INT_MAX >> 1);
	auto dp =
		[&buf, n1, K](int x, int y, int z) -> int&
	{
		int i = (x * n1 + y) * (K + 1) + z;
		assert(static_cast<size_t>(i) < buf.size());
		return buf[i];
	};

	for (int i = 1; i <= len; ++i)
		dp(i, i, 1) = 0;

	for (int T = 2; T <= len; ++T)
		for (int L = 1; L <= len - T + 1; ++L)
		{
			int R = L + T - 1;
			for (int k = 2; k <= K; ++k)
			{
				int val = dp(L, R, k);
				for (int t = L; t < R; ++t)
					val = min(val, dp(L, t, k - 1) + dp(t + 1, R, 1));
				dp(L, R, k) = val;
			}
			dp(L, R, 1) = min(dp(L, R, 1),
				dp(L, R, K) + acmlt[R] - acmlt[L - 1]);
		}

	return dp(1, len, 1);
}


int main()
{
	vector<int>
		a = { 3, 2, 4, 1 },
		b = { 3, 2, 4, 1 },
		c = { 3, 5, 1, 2, 6 };
	OutExpr(mergeStones(a, 2), "%d");
	OutExpr(mergeStones(b, 3), "%d");
	OutExpr(mergeStones(c, 3), "%d");
}
