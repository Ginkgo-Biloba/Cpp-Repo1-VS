#include "leetcode.hpp"

/* 1745. 回文串分割 IV

给你一个字符串 s ，如果可以将它分割成三个 非空 回文子字符串，那么返回 true ，否则返回 false 。

当一个字符串正着读和反着读是一模一样的，就称其为 回文字符串 。

示例 1：
输入：s = "abcbdd"
输出：true
解释："abcbdd" = "a" + "bcb" + "dd"，三个子字符串都是回文的。

示例 2：
输入：s = "bcbddxy"
输出：false
解释：s 没办法被分割成 3 个回文子字符串。

提示：
	3 <= s.length <= 2000
	s​​​​​​ 只包含小写英文字母。
*/

bool checkPartitioning(string s)
{
	int len = static_cast<int>(s.size());
	vector<array<char, 2000>> dp(len);
	memset(dp.data(), 0, sizeof(dp[0]) * dp.size());
	for (int i = 0; i < len; ++i)
		dp[i][i] = 1;
	for (int i = 1; i < len; ++i)
		dp[i - 1][i] = (s[i - 1] == s[i]);
	for (int d = 2; d < len; ++d)
		for (int i = 0; i < len - d; ++i)
		{
			int k = i + d;
			dp[i][k] = dp[i + 1][k - 1] && (s[i] == s[k]);
		}
	for (int i = 0; i < len - 2; ++i)
		for (int k = i + 1; k < len - 1; ++k)
		{
			if (dp[0][i] & dp[i + 1][k] & dp[k + 1][len - 1])
				return true;
		}
	return false;
}


int main()
{
	OutBool(checkPartitioning("abcbdd"));
	OutBool(checkPartitioning("bcbddxy"));
}
