#include "leetcode.hpp"

/* 1220. 统计元音字母序列的数目

给你一个整数 n，请你帮忙统计一下我们可以按下述规则形成多少个长度为 n 的字符串：
	字符串中的每个字符都应当是小写元音字母（'a', 'e', 'i', 'o', 'u'）
	每个元音 'a' 后面都只能跟着 'e'
	每个元音 'e' 后面只能跟着 'a' 或者是 'i'
	每个元音 'i' 后面 不能 再跟着另一个 'i'
	每个元音 'o' 后面只能跟着 'i' 或者是 'u'
	每个元音 'u' 后面只能跟着 'a'

由于答案可能会很大，所以请你返回 模 10^9 + 7 之后的结果。

示例 1：
输入：n = 1
输出：5
解释：所有可能的字符串分别是："a", "e", "i" , "o" 和 "u"。

示例 2：
输入：n = 2
输出：10
解释：所有可能的字符串分别是："ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" 和 "ua"。

示例 3：
输入：n = 5
输出：68

提示：
	1 <= n <= 2 * 10^4
*/

int countVowelPermutation(int n)
{
	int const Mod = 1e9 + 7;
	array<int, 5> cur, buf;
	for (int i = 0; i < 5; ++i)
		cur[i] = 1;
	for (--n; n > 0; --n)
	{
		memset(&buf, 0, sizeof(buf));
		// a
		buf[1] = (buf[1] + cur[0]) % Mod;
		// e
		buf[0] = (buf[0] + cur[1]) % Mod;
		buf[2] = (buf[2] + cur[1]) % Mod;
		// i
		buf[0] = (buf[0] + cur[2]) % Mod;
		buf[1] = (buf[1] + cur[2]) % Mod;
		buf[3] = (buf[3] + cur[2]) % Mod;
		buf[4] = (buf[4] + cur[2]) % Mod;
		// o
		buf[2] = (buf[2] + cur[3]) % Mod;
		buf[4] = (buf[4] + cur[3]) % Mod;
		// u
		buf[0] = (buf[0] + cur[4]) % Mod;
		cur = buf;
	}
	for (int i = 1; i < 5; ++i)
		cur[0] = (cur[0] + cur[i]) % Mod;
	return cur[0];
}


int main()
{
	OutExpr(countVowelPermutation(2), "%d");
	OutExpr(countVowelPermutation(5), "%d");
}
