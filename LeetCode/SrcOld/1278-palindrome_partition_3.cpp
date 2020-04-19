#include "leetcode.hpp"

/* 1278. 分割回文串 III

给你一个由小写字母组成的字符串 s，和一个整数 k。

请你按下面的要求分割字符串：
	首先，你可以将 s 中的部分字符修改为其他的小写英文字母。
	接着，你需要把 s 分割成 k 个非空且不相交的子串，并且每个子串都是回文串。

请返回以这种方式分割字符串所需修改的最少字符数。

示例 1：
输入：s = "abc", k = 2
输出：1
解释：你可以把字符串分割成 "ab" 和 "c"，并修改 "ab" 中的 1 个字符，将它变成回文串。

示例 2：
输入：s = "aabbc", k = 3
输出：0
解释：你可以把字符串分割成 "aa"、"bb" 和 "c"，它们都是回文串。

示例 3：
输入：s = "leetcode", k = 8
输出：0

提示：
	1 <= k <= s.length <= 100
	s 中只含有小写英文字母。
*/

// https://leetcode.com/problems/palindrome-partitioning-iii/discuss/498677/Step-by-Step-solution-DP-(Java)
// 抄的
int getcost(string const& S, int i, int j)
{
	int c = 0;
	for (; i < j; ++i, --j)
		c += (S[i] != S[j]);
	return c;
}

int palindromePartition(string S, int k)
{
	int len = static_cast<int>(S.size());
	vector<array<int, 101>> dp(k + 1), cost(len);

	for (int i = 0; i < len; ++i)
		cost[i][i] = 0;
	for (int i = 0; i < len - 1; ++i)
		for (int j = i + 1; j < len; ++j)
			cost[i][j] = getcost(S, i, j);

	for (int i = 0; i < len; ++i)
		dp[1][i] = cost[0][i];
	for (int i = 2; i <= k; ++i)
		for (int j = i - 1; j < len; j++)
		{
			int d = len;
			for (int h = j - 1; h >= 0; --h)
				d = min(d, dp[i - 1][h] + cost[h + 1][j]);
			dp[i][j] = d;
		}
	return dp[k][len - 1];
}


int main()
{
	OutExpr(palindromePartition("abc", 2), "%d");
	OutExpr(palindromePartition("aabbc", 3), "%d");
	OutExpr(palindromePartition("leetcode", 8), "%d");
}
