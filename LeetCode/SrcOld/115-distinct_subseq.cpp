#include "leetcode.hpp"

/* 115. 不同的子序列

给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。

一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。
例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是。

题目数据保证答案符合 32 位带符号整数范围。

示例 1：

输入：S = "rabbbit", T = "rabbit"
输出：3
解释：

如下图所示, 有 3 种可以从 S 中得到 "rabbit" 的方案。
(上箭头符号 ^ 表示选取的字母)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^

示例 2：

输入：S = "babgbag", T = "bag"
输出：5
解释：

如下图所示, 有 5 种可以从 S 中得到 "bag" 的方案。
(上箭头符号 ^ 表示选取的字母)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
	^  ^^
babgbag
		^^^
*/

// https://leetcode.com/problems/distinct-subsequences/discuss/37316/7-10-lines-C%2B%2B-Solutions-with-Detailed-Explanations-(O(m*n)-time-and-O(m)-space)
// 抄的
int numDistinct(string s, string t)
{
	int a = static_cast<int>(s.length());
	int b = static_cast<int>(t.length());
	// if (a < b) return 0;
	vector<unsigned> dp(b + 1), eq(b + 1);
	dp[0] = eq[0] = 1;
	for (int i = 0; i < a; ++i)
	{
		eq.swap(dp);
		for (int k = 0; k < b; ++k)
		{
			// 不要或者要
			if (s[i] == t[k])
				dp[k + 1] = eq[k + 1] + eq[k];
			// 只能不要
			else
				dp[k + 1] = eq[k + 1];
		}
	}
	return dp[b];
}


int main()
{
	OutExpr(numDistinct("rabbbit", "rabbit"), "%d");
	OutExpr(numDistinct("babgbag", "bag"), "%d");
}
