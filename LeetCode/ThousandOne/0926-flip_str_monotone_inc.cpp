#include "leetcode.hpp"

/* 926. 将字符串翻转到单调递增

如果一个由 '0' 和 '1' 组成的字符串，是以一些 '0'（可能没有 '0'）后面跟着一些 '1'（也可能没有 '1'）的形式组成的，那么该字符串是单调递增的。

我们给出一个由字符 '0' 和 '1' 组成的字符串 S，我们可以将任何 '0' 翻转为 '1' 或者将 '1' 翻转为 '0'。

返回使 S 单调递增的最小翻转次数。

示例 1：
输入："00110"
输出：1
解释：我们翻转最后一位得到 00111.

示例 2：
输入："010110"
输出：2
解释：我们翻转得到 011111，或者是 000111。

示例 3：
输入："00011000"
输出：2
解释：我们翻转得到 00000000。

提示：
	1 <= S.length <= 20000
	S 中只包含字符 '0' 和 '1'
*/

int minFlipsMonoIncr(string S)
{
	int len = static_cast<int>(S.size());
	int s0 = 0, s1 = 0;
	int n0 = 0, n1 = 0, ans;

	for (int i = 0; i < len; ++i)
	{
		s0 += S[i] == '0';
		s1 += S[i] == '1';
	}
	ans = min(s0, s1);
	// 从 i 后面断开，后面的 0 和前面的 1 都需要翻转
	for (int i = 0; i < len; ++i)
	{
		n0 += S[i] == '0';
		n1 += S[i] == '1';
		ans = min(ans, n1 + s0 - n0);
	}
	return ans;
}

int main()
{
	OutExpr(minFlipsMonoIncr("00110"), "%d");
	OutExpr(minFlipsMonoIncr("010110"), "%d");
	OutExpr(minFlipsMonoIncr("00011000"), "%d");
	OutExpr(minFlipsMonoIncr("10011111110010111011"), "%d");
}
