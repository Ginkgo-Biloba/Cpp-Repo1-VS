#include "leetcode.hpp"

/* 859. 亲密字符串

给定两个由小写字母构成的字符串 A 和 B，只要我们可以通过交换 A 中的两个字母得到与 B 相等的结果，就返回 true；否则返回 false 。

示例 1：
输入： A = "ab", B = "ba"
输出： true

示例 2：
输入： A = "ab", B = "ab"
输出： false

示例 3:
输入： A = "aa", B = "aa"
输出： true

示例 4：
输入： A = "aaaaaaabc", B = "aaaaaaacb"
输出： true

示例 5：
输入： A = "", B = "aa"
输出： false

提示：
	0 <= A.length <= 20000
	0 <= B.length <= 20000
	A 和 B 仅由小写字母构成。
*/

bool buddyStrings(string A, string B)
{
	size_t len = A.size();
	if (len != B.size())
		return false;

	size_t x[2];
	int d = 0, hist[26] = { 0 };

	for (size_t i = 0; i < len; ++i)
	{
		++(hist[A[i] - 'a']);
		if (A[i] != B[i])
		{
			if (d == 2)
				return false;
			x[d] = i;
			++d;
		}
	}

	if (d == 2)
		return (A[x[0]] == B[x[1]]) && (A[x[1]] == B[x[0]]);

	if (d == 0)
		for (int i = 0; i < 26; ++i)
		{
			if (hist[i] > 1)
				return true;
		}

	return false;
}


int main()
{
	OutBool(buddyStrings("ab", "ba"));
	OutBool(buddyStrings("ab", "ab"));
	OutBool(buddyStrings("aa", "aa"));
	OutBool(buddyStrings("aaaaaaabc", "aaaaaaacb"));
	OutBool(buddyStrings("", "aa"));
}
