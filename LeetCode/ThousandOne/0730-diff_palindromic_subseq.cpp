#include "leetcode.hpp"

/* 730. 统计不同回文子字符串

给定一个字符串 S，找出 S 中不同的非空回文子序列个数，并返回该数字与 10^9 + 7 的模。
通过从 S 中删除 0 个或多个字符来获得子字符序列。
如果一个字符序列与它反转后的字符序列一致，那么它是回文字符序列。
如果对于某个  i，A_i != B_i，那么 A_1, A_2, ... 和 B_1, B_2, ... 这两个字符序列是不同的。

示例 1：
输入：
S = 'bccb'
输出：6
解释：
6 个不同的非空回文子字符序列分别为：'b', 'c', 'bb', 'cc', 'bcb', 'bccb'。
注意：'bcb' 虽然出现两次但仅计数一次。

示例 2：
输入：
S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
输出：104860361
解释：
共有 3104860382 个不同的非空回文子字符序列，对 10^9 + 7 取模为 104860361。

提示：
	字符串 S 的长度将在[1, 1000]范围内。
	每个字符 S[i] 将会是集合 {'a', 'b', 'c', 'd'} 中的某一个。
*/

// https://leetcode.com/problems/count-different-palindromic-subsequences/discuss/109507/Java-96ms-DP-Solution-with-Detailed-Explanation
// 抄的
int countPalindromicSubsequences(string str)
{
	int const mod = 1e9 + 7;
	int const len = static_cast<int>(str.size());
	vector<int> dp(len * len);
	auto at = [len](int y, int x) { return y * len + x; };

	// 单个字符
	for (int i = 0; i < len; ++i)
		dp[at(i, i)] = 1;

	for (int d = 1; d < len; ++d)
		for (int i = 0; i < len - d; ++i)
		{
			int k = i + d, val;
			if (str[i] == str[k])
			{
				// 用来处理重复
				int lo = i + 1, hi = k - 1;
				while (lo <= hi && str[lo] != str[k])
					++lo;
				while (lo <= hi && str[hi] != str[i])
					--hi;
				if (lo > hi)
				{
					// 考虑 a...a... 左边和右边的 a 中间没有其他的 a
					val = dp[at(i + 1, k - 1)] * 2 + 2;
				}
				else if (lo == hi)
				{
					// 考虑 a...a...a 左边和右边的 a 中间有 1 个 a
					val = dp[at(i + 1, k - 1)] * 2 + 1;
				}
				else
				{
					// 考虑 a...a...a...a 左边和右边的 a 中间有至少 2 个 a
					val = dp[at(i + 1, k - 1)] * 2 - dp[at(lo + 1, hi - 1)];
				}
			}
			else
			{
				// !(tr[i] == str[k])
				val = dp[at(i, k - 1)] + dp[at(i + 1, k)] - dp[at(i + 1, k - 1)];
			}
			dp[at(i, k)] = val < 0 ? (val + mod) : (val % mod);
		}

	return dp[at(0, len - 1)];
}


int main()
{
	OutExpr(countPalindromicSubsequences("aab"), "%d");
	OutExpr(countPalindromicSubsequences("bccb"), "%d");
	OutExpr(countPalindromicSubsequences(
		"abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"),
		"%d");
}
