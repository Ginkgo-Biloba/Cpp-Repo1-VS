#include "leetcode.hpp"

/* 903. DI 序列的有效排列

我们给出 S，一个源于 {'D', 'I'} 的长度为 n 的字符串 。
这些字母代表 “减少” 和 “增加”。
有效排列 是对整数 {0, 1, ..., n} 的一个排列 P[0], P[1], ..., P[n]，使得对所有的 i：
	如果 S[i] == 'D'，那么 P[i] > P[i+1]，以及；
	如果 S[i] == 'I'，那么 P[i] < P[i+1]。

有多少个有效排列？因为答案可能很大，所以请返回你的答案模 10^9 + 7.

示例：
输入："DID"
输出：5
解释：
(0, 1, 2, 3) 的五个有效排列是：
(1, 0, 3, 2)
(2, 0, 3, 1)
(2, 1, 3, 0)
(3, 0, 2, 1)
(3, 1, 2, 0)

提示：
	1 <= S.length <= 200
	S 仅由集合 {'D', 'I'} 中的字符组成。
*/

// https://leetcode.com/problems/valid-permutations-for-di-sequence/discuss/168278/C%2B%2BJavaPython-DP-Solution-O(N2)
// 抄的
int numPermsDISequence(string s)
{
	int const Mod = 1e9 + 7;
	int n = static_cast<int>(s.size());
	vector<vector<int>> dp(n + 1, vector<int>(n + 1));

	for (int i = 0; i <= n; ++i)
		dp[0][i] = 1;
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == 'I')
		{
			int k = 0, cur = 0;
			for (; k < n - i; ++k)
				dp[i + 1][k] = cur = (cur + dp[i][k]) % Mod;
		}
		else
		{
			int k = n - i - 1, cur = 0;
			for (; k >= 0; --k)
				dp[i + 1][k] = cur = (cur + dp[i][k + 1]) % Mod;
		}
	}
	return dp[n][0];
}

int main()
{
	OutExpr(numPermsDISequence("DID"), "%d");
	OutExpr(numPermsDISequence("DIDD"), "%d");
}
