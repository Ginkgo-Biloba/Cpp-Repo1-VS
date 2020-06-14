#include "leetcode.hpp"

/* 1461. 检查一个字符串是否包含所有长度为 K 的二进制子串

给你一个二进制字符串 s 和一个整数 k 。

如果所有长度为 k 的二进制字符串都是 s 的子串，请返回 True ，否则请返回 False 。

示例 1：

输入：s = "00110110", k = 2
输出：true
解释：长度为 2 的二进制串包括 "00"，"01"，"10" 和 "11"。
它们分别是 s 中下标为 0，1，3，2 开始的长度为 2 的子串。

示例 2：
输入：s = "00110", k = 2
输出：true

示例 3：
输入：s = "0110", k = 1
输出：true
解释：长度为 1 的二进制串包括 "0" 和 "1"，显然它们都是 s 的子串。

示例 4：
输入：s = "0110", k = 2
输出：false
解释：长度为 2 的二进制串 "00" 没有出现在 s 中。

示例 5：
输入：s = "0000000001011100", k = 4
输出：false

提示：
	1 <= s.length <= 5 * 10^5
	s 中只含 0 和 1 。
	1 <= k <= 20
*/

bool hasAllCodes(string s, int k)
{
	int mask = (1 << k) - 1;
	vector<char> M(mask + 1, 0);
	int len = static_cast<int>(s.length());
	int cur = 0, sum = 0, i = 0;
	if (len < (mask + k))
		return false;

	for (; i < k - 1; ++i)
		cur = (cur << 1) | (s[i] - '0');
	for (; i < len; ++i)
	{
		cur = ((cur << 1) | (s[i] - '0'));
		cur &= mask;
		sum += M[cur] == 0;
		M[cur] = 1;
	}
	return sum == (1 << k);
}


int main()
{
	OutBool(hasAllCodes("00110110", 2));
	OutBool(hasAllCodes("00110", 2));
	OutBool(hasAllCodes("0110", 1));
	OutBool(hasAllCodes("0110", 2));
	OutBool(hasAllCodes("0000000001011100", 4));
}
