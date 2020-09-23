#include "leetcode.hpp"

/* 1397. 找到所有好字符串

给你两个长度为 n 的字符串 s1 和 s2 ，以及一个字符串 evil 。请你返回 好字符串 的数目。

好字符串 的定义为：它的长度为 n ，字典序大于等于 s1 ，字典序小于等于 s2 ，且不包含 evil 为子字符串。

由于答案可能很大，请你返回答案对 10^9 + 7 取余的结果。

示例 1：
输入：n = 2, s1 = "aa", s2 = "da", evil = "b"
输出：51
解释：总共有 25 个以 'a' 开头的好字符串："aa"，"ac"，"ad"，...，"az"。还有 25 个以 'c' 开头的好字符串："ca"，"cc"，"cd"，...，"cz"。最后，还有一个以 'd' 开头的好字符串："da"。

示例 2：
输入：n = 8, s1 = "leetcode", s2 = "leetgoes", evil = "leet"
输出：0
解释：
所有字典序大于等于 s1 且小于等于 s2 的字符串都以 evil 字符串 "leet" 开头。
所以没有好字符串。

示例 3：
输入：n = 2, s1 = "gx", s2 = "gz", evil = "x"
输出：2

提示：
	s1.length == n
	s2.length == n
	s1 <= s2
	1 <= n <= 500
	1 <= evil.length <= 50
	所有字符串都只包含小写英文字母。
*/

static int const Mod = 1e9 + 7;

// https://leetcode.com/problems/find-all-good-strings/discuss/558812/C%2B%2B-DP-%2B-KMP
// 抄的
class Solution
{
	vector<int> kmp;
	int dp[501][51][2][2];
	string s1, s2, evil;
	int n, elen;

	int dfs(int sp, int ep, bool i1, bool i2)
	{
		if (ep == elen)
			return 0;
		if (sp == n)
			return 1;
		int* ptr = &(dp[sp][ep][i1][i2]);
		if (*ptr == 0)
		{
			char ch = (i1 ? s1[sp] : 'a');
			char chend = (i2 ? s2[sp] : 'z');
			for (; ch <= chend; ++ch)
			{
				int ie = ep;
				while (ie > 0 && ch != evil[ie])
					ie = kmp[ie - 1];
				int new_ep = (ch == evil[ie] ? ie + 1 : 0);
				int delta = dfs(sp + 1, new_ep,
					i1 && (ch == s1[sp]), i2 && (ch == s2[sp]));
				*ptr = (*ptr + delta) % Mod;
			}
		}
		return *ptr;
	}

public:
	int findGoodStrings(int n_, string s1_, string s2_, string evil_)
	{
		n = n_;
		s1.swap(s1_);
		s2.swap(s2_);
		evil.swap(evil_);
		elen = static_cast<int>(evil.size());
		kmp.resize(elen);
		for (int h = 0, i = 1; i < elen; ++i)
		{
			if (evil[i] == evil[h])
				kmp[i] = ++h;
			else if (h > 0)
			{
				h = kmp[h - 1];
				--i;
			}
		}

		memset(dp, 0, sizeof(dp));
		return dfs(0, 0, true, true);
	}
};


int main()
{
	Solution s;
	OutExpr(s.findGoodStrings(2, "aa", "da", "b"), "%d");
	OutExpr(s.findGoodStrings(8, "leetcode", "leetgoes", "leet"), "%d");
	OutExpr(s.findGoodStrings(2, "gx", "gz", "x"), "%d");
}
