#include "leetcode.hpp"

/* 1573. 分割字符串的方案数

给你一个二进制串 s  （一个只包含 0 和 1 的字符串），我们可以将 s 分割成 3 个 非空 字符串 s1, s2, s3 （s1 + s2 + s3 = s）。

请你返回分割 s 的方案数，满足 s1，s2 和 s3 中字符 '1' 的数目相同。

由于答案可能很大，请将它对 10^9 + 7 取余后返回。

示例 1：
输入：s = "10101"
输出：4
解释：总共有 4 种方法将 s 分割成含有 '1' 数目相同的三个子字符串。
"1|010|1"
"1|01|01"
"10|10|1"
"10|1|01"

示例 2：
输入：s = "1001"
输出：0

示例 3：
输入：s = "0000"
输出：3
解释：总共有 3 种分割 s 的方法。
"0|0|00"
"0|00|0"
"00|0|0"

示例 4：
输入：s = "100100010100110"
输出：12

提示：
	s[i] == '0' 或者 s[i] == '1'
	3 <= s.length <= 10^5
*/

int numWays(string s)
{
	int64_t const mod = 1e9 + 7;
	int64_t ans = 1;
	int len = static_cast<int>(s.length());
	int num = 0, cur = 0;
	for (int i = 0; i < len; ++i)
		num += (s[i] == '1');

	if ((len < 3) || (num % 3))
		return 0;
	if (num == 0)
	{
		ans = static_cast<int64_t>(len - 1);
		ans = ans * (len - 2) / 2 % mod;
		return static_cast<int>(ans);
	}

	num /= 3;
	for (int i = 0; i < len; ++i)
	{
		cur += (s[i] == '1');
		if (cur == num)
		{
			num *= 2;
			int k = i + 1;
			for (; k < len; ++k)
			{
				if (s[k] == '1')
					break;
			}
			ans *= static_cast<int64_t>(k - i);
		}
	}
	return static_cast<int>(ans % mod);
}


int main()
{
	OutExpr(numWays("10101"), "%d");
	OutExpr(numWays("1001"), "%d");
	OutExpr(numWays("0000"), "%d");
	OutExpr(numWays("100100010100110"), "%d");
}
