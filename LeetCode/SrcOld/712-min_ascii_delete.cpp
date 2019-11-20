#include "leetcode.hpp"

/* 712. 两个字符串的最小ASCII删除和

给定两个字符串s1, s2，找到使两个字符串相等所需删除字符的ASCII值的最小和。

示例 1:
输入: s1 = "sea", s2 = "eat"
输出: 231
解释: 在 "sea" 中删除 "s" 并将 "s" 的值(115)加入总和。
在 "eat" 中删除 "t" 并将 116 加入总和。
结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。

示例 2:
输入: s1 = "delete", s2 = "leet"
输出: 403
解释: 在 "delete" 中删除 "dee" 字符串变成 "let"，
将 100[d]+101[e]+101[e] 加入总和。在 "leet" 中删除 "e" 将 101[e] 加入总和。
结束时，两个字符串都等于 "let"，结果即为 100+101+101+101 = 403 。
如果改为将两个字符串转换为 "lee" 或 "eet"，我们会得到 433 或 417 的结果，比答案更大。

注意:
	0 < s1.length, s2.length <= 1000。
	所有字符串中的字符ASCII值在[97, 122]之间。
*/


int minimumDeleteSum_old(string s1, string s2)
{
	int const n1 = static_cast<int>(s1.size());
	int const n2 = static_cast<int>(s2.size());
	vector<int> dp((n1 + 1) * (n2 + 1));
	auto at = [n2](int y, int x) -> int { return y * (n2 + 1) + x; };
	int sum1 = 0, sum2 = 0;

	for (int i2 = 1; i2 <= n2; ++i2)
	{
		sum2 += s2[i2 - 1];
		dp[at(0, i2)] = sum2;
	}
	dp[at(0, n2)] = sum2;
	for (int i1 = 1; i1 <= n1; ++i1)
	{
		sum1 += s1[i1 - 1];
		dp[at(i1, 0)] = sum1;
		for (int i2 = 1; i2 <= n2; ++i2)
		{
			if (s1[i1 - 1] == s2[i2 - 1])
				dp[at(i1, i2)] = dp[at(i1 - 1, i2 - 1)];
			else
				dp[at(i1, i2)] = std::min(
					dp[at(i1 - 1, i2)] + s1[i1 - 1],
					dp[at(i1, i2 - 1)] + s2[i2 - 1]);
		}
	}
	return dp[at(n1, n2)];
}


int minimumDeleteSum(string const& s1, string const& s2)
{
	int const n1 = static_cast<int>(s1.size());
	int const n2 = static_cast<int>(s2.size());
	vector<int> pre(n2 + 1), cur(n2 + 1);
	int sum1 = 0, sum2 = 0;

	for (int i2 = 1; i2 <= n2; ++i2)
	{
		sum2 += s2[i2 - 1];
		cur[i2] = sum2;
	}
	cur[n2] = sum2;
	for (int i1 = 1; i1 <= n1; ++i1)
	{
		pre.swap(cur);
		sum1 += s1[i1 - 1];
		cur[0] = sum1;
		for (int i2 = 1; i2 <= n2; ++i2)
		{
			if (s1[i1 - 1] == s2[i2 - 1])
				cur[i2] = pre[i2 - 1];
			else
				cur[i2] = std::min(
					pre[i2] + s1[i1 - 1],
					cur[i2 - 1] + s2[i2 - 1]);
		}
	}
	return cur[n2];
}


int main()
{
	OutExpr(minimumDeleteSum("", ""), "%d");
	OutExpr(minimumDeleteSum("sea", "eat"), "%d");
	OutExpr(minimumDeleteSum("delete", "leet"), "%d");
}
