#include "leetcode.hpp"

/* 1016. 子串能表示从 1 到 N 数字的二进制串

给定一个二进制字符串 S（一个仅由若干 '0' 和 '1' 构成的字符串）和一个正整数 N，如果对于从 1 到 N 的每个整数 X，其二进制表示都是 S 的子串，就返回 true，否则返回 false。

示例 1：
输入：S = "0110", N = 3
输出：true

示例 2：
输入：S = "0110", N = 4
输出：false

提示：
	1 <= S.length <= 1000
	1 <= N <= 10^9
*/

// https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/discuss/260847/JavaC++Python-O(S)/252984
// 抄的
bool queryString(string S, int N)
{
	char buf[32] = { 0 };
	// 如果包含 N，那么肯定包含 N/2 = N >> 1
	for (int i = N / 2 + 1; i <= N; ++i)
	{
		int ib = 31;
		for (int k = i; k; k >>= 1)
			buf[--ib] = static_cast<char>((k & 1) + '0');
		if (strstr(S.c_str(), buf + ib) == NULL)
			return false;
	}
	return true;
}


int main()
{
	OutBool(queryString("0110", 3));
	OutBool(queryString("0110", 4));
}
