#include "leetcode.hpp"

/* 1223. 掷骰子模拟

有一个骰子模拟器会每次投掷的时候生成一个 1 到 6 的随机数。

不过我们在使用它时有个约束，就是使得投掷骰子时，连续 掷出数字 i 的次数不能超过 rollMax[i]。
i 从 1 开始编号。

现在，给你一个整数数组 rollMax 和一个整数 n，请你来计算掷 n 次骰子可得到的不同点数序列的数量。

假如两个序列中至少存在一个元素不同，就认为这两个序列是不同的。
由于答案可能很大，所以请返回 模 10^9 + 7 之后的结果。

示例 1：
输入：n = 2, rollMax = [1,1,2,2,2,3]
输出：34
解释：我们掷 2 次骰子，如果没有约束的话，共有 6 * 6 = 36 种可能的组合。但是根据 rollMax 数组，数字 1 和 2 最多连续出现一次，所以不会出现序列 (1,1) 和 (2,2)。因此，最终答案是 36-2 = 34。

示例 2：
输入：n = 2, rollMax = [1,1,1,1,1,1]
输出：30

示例 3：
输入：n = 3, rollMax = [1,1,1,2,2,3]
输出：181

提示：
	1 <= n <= 5000
	rollMax.length == 6
	1 <= rollMax[i] <= 15
*/

// https://leetcode.com/problems/dice-roll-simulation/discuss/403756/Java-Share-my-DP-solution
// 抄的
class Solution
{
public:
	int dieSimulator(int n, vector<int>& rollMax)
	{
		int64_t Mod = 1e9 + 7;
		vector<array<int64_t, 7>> dp(n);
		dp[0].fill(1);
		dp[0][6] = 6;
		for (int i = 1; i < n; ++i)
		{
			int64_t sum = 0;
			for (int k = 0; k < 6; ++k)
			{
				dp[i][k] = dp[i - 1][6];
				if (i - rollMax[k] < 0)
					sum = sum + dp[i][k];
				else
				{
					if (i - rollMax[k] >= 1)
						dp[i][k] -= dp[i - rollMax[k] - 1][6] - dp[i - rollMax[k] - 1][k];
					else
						dp[i][k] -= 1;
					dp[i][k] = (dp[i][k] + Mod) % Mod;
					sum += dp[i][k];
				}
			}
			dp[i][6] = sum % Mod;
		}
		return static_cast<int>(dp[n - 1][6]);
	}
};


int main()
{
	vector<int>
		a = { 1, 1, 2, 2, 2, 3 },
		b = { 1, 1, 1, 1, 1, 1 },
		c = { 1, 1, 1, 2, 2, 3 };
	Solution s;
	OutExpr(s.dieSimulator(2, a), "%d");
	OutExpr(s.dieSimulator(2, b), "%d");
	OutExpr(s.dieSimulator(3, c), "%d");
}
