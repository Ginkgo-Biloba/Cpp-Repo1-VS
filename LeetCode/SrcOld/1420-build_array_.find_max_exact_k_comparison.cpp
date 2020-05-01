#include "leetcode.hpp"

/* 1420. 生成数组

给你三个整数 n、m 和 k 。
下图描述的算法用于找出正整数数组中最大的元素。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/04/19/e.png

请你生成一个具有下述属性的数组 arr ：
	arr 中有 n 个整数。
	1 <= arr[i] <= m 其中 (0 <= i < n) 。
	将上面提到的算法应用于 arr ，search_cost 的值等于 k 。

返回上述条件下生成数组 arr 的 方法数 ，由于答案可能会很大，所以 必须 对 10^9 + 7 取余。

示例 1：
输入：n = 2, m = 3, k = 1
输出：6
解释：可能的数组分别为 [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]

示例 2：
输入：n = 5, m = 2, k = 3
输出：0
解释：没有数组可以满足上述条件

示例 3：
输入：n = 9, m = 1, k = 1
输出：1
解释：可能的数组只有 [1, 1, 1, 1, 1, 1, 1, 1, 1]

示例 4：
输入：n = 50, m = 100, k = 25
输出：34549172
解释：不要忘了对 1000000007 取余

示例 5：
输入：n = 37, m = 17, k = 7
输出：418930126

提示：
	1 <= n <= 50
	1 <= m <= 100
	0 <= k <= n
*/

// https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/discuss/591186/C%2B%2B-DP-solution-4ms-98-w-explanation
// 抄的，还是不会
class Solution
{
	// ways of filling up array[0 ... i] with cost j and maximum value less than or equal tok.
	int64_t dp[50][51][101];

public:
	int numOfArrays(int n, int m, int k)
	{
		int64_t const Mod = 1e9 + 7;
		memset(dp, 0, sizeof(dp));
		for (int a = 0; a < n; ++a)
			for (int b = 1; b <= k; ++b)
				for (int c = b; c <= m; ++c)
				{
					int64_t val = dp[a][b][c - 1];
					if (a == 0)
						val += (b == 1);
					else
					{
						val += dp[a - 1][b - 1][c - 1]
							+ c * (dp[a - 1][b][c] + Mod - dp[a - 1][b][c - 1]);
					}
					dp[a][b][c] = val % Mod;
				}
		return static_cast<int>(dp[n - 1][k][m] % Mod);
	}
};


int main()
{
	Solution s;
	OutExpr(s.numOfArrays(2, 3, 1), "%d");
	OutExpr(s.numOfArrays(5, 2, 3), "%d");
	OutExpr(s.numOfArrays(9, 1, 1), "%d");
	OutExpr(s.numOfArrays(50, 100, 25), "%d");
	OutExpr(s.numOfArrays(37, 17, 7), "%d");
}
