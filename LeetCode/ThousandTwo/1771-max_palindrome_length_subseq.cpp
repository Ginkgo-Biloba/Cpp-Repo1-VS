#include "leetcode.hpp"

/* 1771. 由子序列构造的最长回文串的长度

给你两个字符串 word1 和 word2 ，请你按下述方法构造一个字符串：
	从 word1 中选出某个 非空 子序列 subsequence1 。
	从 word2 中选出某个 非空 子序列 subsequence2 。
	连接两个子序列 subsequence1 + subsequence2 ，得到字符串。

返回可按上述方法构造的最长 回文串 的 长度 。
如果无法构造回文串，返回 0 。

字符串 s 的一个 子序列 是通过从 s 中删除一些（也可能不删除）字符而不更改其余字符的顺序生成的字符串。

回文串 是正着读和反着读结果一致的字符串。

示例 1：
输入：word1 = "cacb", word2 = "cbba"
输出：5
解释：从 word1 中选出 "ab" ，从 word2 中选出 "cba" ，得到回文串 "abcba" 。

示例 2：
输入：word1 = "ab", word2 = "ab"
输出：3
解释：从 word1 中选出 "ab" ，从 word2 中选出 "a" ，得到回文串 "aba" 。

示例 3：
输入：word1 = "aa", word2 = "bb"
输出：0
解释：无法按题面所述方法构造回文串，所以返回 0 。

提示：
	1 <= word1.length, word2.length <= 1000
	word1 和 word2 由小写英文字母组成
*/

// https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/discuss/1075453/C%2B%2B-LPS-with-picture
// 抄的
class Solution
{
	vector<array<int, 2002>> dp;

	void lps(string s)
	{
		int len = static_cast<int>(s.size() + 1);
		dp.resize(len + 1);
		for (int d = 1; d <= len; ++d)
			for (int i = 0; i + d <= len; ++i)
			{
				if (s[i] == s[i + d - 1])
					dp[i][i + d] = dp[i + 1][i + d - 1] + (d == 1 ? 1 : 2);
				else
					dp[i][i + d] = max(dp[i][i + d - 1], dp[i + 1][i + d]);
			}
	}

public:
	int longestPalindrome(string a, string b)
	{
		int m = static_cast<int>(a.size());
		int n = static_cast<int>(b.size());
		int ans = 0;
		lps(a + b);
		for (int i = 0; i < m; ++i)
			for (int j = n - 1; j >= 0; --j)
				if (a[i] == b[j])
				{
					ans = max(ans, dp[i][m + j + 1]);
					break;
				}
		return ans;
	}
};


int main()
{
	Solution s;
	OutExpr(s.longestPalindrome("cacb", "cbba"), "%d");
	OutExpr(s.longestPalindrome("ab", "ab"), "%d");
	OutExpr(s.longestPalindrome("aa", "bb"), "%d");
	OutExpr(s.longestPalindrome("cfe", "ef"), "%d");
}
