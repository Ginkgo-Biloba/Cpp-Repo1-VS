#include "leetcode.hpp"

/* 91. 解码方法

一条包含字母 A-Z 的消息通过以下方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26

给定一个只包含数字的非空字符串，请计算解码方法的总数。

示例 1:
输入: "12"
输出: 2
解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。

示例 2:
输入: "226"
输出: 3
解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6)。
*/

int numDecodings(string s)
{
	if (s.empty())
		return 1;
	int len = static_cast<int>(s.size());
	vector<int> dp(len + 1);
	dp[0] = 1;
	dp[1] = s[0] == '0' ? 0 : 1;
	for (int i = 1; i < len; ++i)
	{
		int p = (s[i - 1] - '0') * 10 + (s[i] - '0');
		if (s[i] != '0')
			dp[i + 1] += dp[i];
		if (10 <= p && p <= 26)
			dp[i + 1] += dp[i - 1];
		if (dp[i + 1] == 0)
			break;
	}
	return dp[len];
}


int main()
{
	OutExpr(numDecodings("12"), "%d");
	OutExpr(numDecodings("226"), "%d");
	OutExpr(numDecodings("2316"), "%d");
	OutExpr(numDecodings("2306"), "%d");
	OutExpr(numDecodings("026"), "%d");
	OutExpr(numDecodings(""), "%d");
}
