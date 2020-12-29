#include "leetcode.hpp"

/* 1662. 检查两个字符串数组是否相等

给你两个字符串数组 word1 和 word2 。
如果两个数组表示的字符串相同，返回 true ；否则，返回 false 。

数组表示的字符串 是由数组中的所有元素 按顺序 连接形成的字符串。

示例 1：
输入：word1 = ["ab", "c"], word2 = ["a", "bc"]
输出：true
解释：
word1 表示的字符串为 "ab" + "c" -> "abc"
word2 表示的字符串为 "a" + "bc" -> "abc"
两个字符串相同，返回 true

示例 2：
输入：word1 = ["a", "cb"], word2 = ["ab", "c"]
输出：false

示例 3：
输入：word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
输出：true

提示：
	1 <= word1.length, word2.length <= 10^3
	1 <= word1[i].length, word2[i].length <= 10^3
	1 <= sum(word1[i].length), sum(word2[i].length) <= 10^3
	word1[i] 和 word2[i] 由小写字母组成
*/

bool arrayStringsAreEqual(vector<string>& A, vector<string>& B)
{
	int alen = static_cast<int>(A.size());
	int blen = static_cast<int>(B.size());
	int va = -1, vb = -1;
	int sa = 0, sb = 0;
	int ia = 0, ib = 0;
	while (va < alen || vb < blen)
	{
		if (ia == sa)
		{
			++va;
			if (va == alen)
				ia = -1;
			else
			{
				sa = static_cast<int>(A[va].size());
				ia = 0;
			}
		}
		if (ib == sb)
		{
			++vb;
			if (vb == blen)
				ib = -1;
			else
			{
				sb = static_cast<int>(B[vb].size());
				ib = 0;
			}
		}
		if (ia == -1 && ib == -1)
			return true;
		if (ia == -1 || ib == -1)
			return false;
		if (A[va][ia] != B[vb][ib])
			return false;
		++ia;
		++ib;
	}
	return true;
}


int main()
{
	vector<string>
		a = { "abc", "d", "defg" },
		b = { "abcddefg" };
	OutBool(arrayStringsAreEqual(a, b));
}
