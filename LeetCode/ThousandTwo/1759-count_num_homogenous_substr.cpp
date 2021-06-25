#include "leetcode.hpp"

/* 1759. 统计同构子字符串的数目

给你一个字符串 s ，返回 s 中 同构子字符串 的数目。
由于答案可能很大，只需返回对 10^9 + 7 取余 后的结果。

同构字符串 的定义为：如果一个字符串中的所有字符都相同，那么该字符串就是同构字符串。

子字符串 是字符串中的一个连续字符序列。

示例 1：
输入：s = "abbcccaa"
输出：13
解释：同构子字符串如下所列：
"a"   出现 3 次。
"aa"  出现 1 次。
"b"   出现 2 次。
"bb"  出现 1 次。
"c"   出现 3 次。
"cc"  出现 2 次。
"ccc" 出现 1 次。
3 + 1 + 2 + 1 + 3 + 2 + 1 = 13

示例 2：
输入：s = "xy"
输出：2
解释：同构子字符串是 "x" 和 "y" 。

示例 3：
输入：s = "zzzzz"
输出：15

提示：
	1 <= s.length <= 10^5
	s 由小写字符串组成
*/

int countHomogenous(string s)
{
	int64_t const mod = static_cast<int>(1e9 + 7);
	int64_t ans = 0;
	int len = static_cast<int>(s.size());
	for (int i = 0; i < len;)
	{
		int k = i + 1;
		while (k < len && s[k] == s[i])
			++k;
		int64_t n = k - i;
		ans = (ans + n * (n + 1) / 2) % mod;
		i = k;
	}
	return static_cast<int>(ans);
}


int main()
{}
