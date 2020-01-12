#include "leetcode.hpp"

/* 984. 不含 AAA 或 BBB 的字符串

给定两个整数 A 和 B，返回任意字符串 S，要求满足：
	S 的长度为 A + B，且正好包含 A 个 'a' 字母与 B 个 'b' 字母；
	子串 'aaa' 没有出现在 S 中；
	子串 'bbb' 没有出现在 S 中。

示例 1：
输入：A = 1, B = 2
输出："abb"
解释："abb", "bab" 和 "bba" 都是正确答案。

示例 2：
输入：A = 4, B = 1
输出："aabaa"

提示：
	0 <= A <= 100
	0 <= B <= 100
	对于给定的 A 和 B，保证存在满足要求的 S。
*/

string strWithout3a3b(int A, int B)
{
	int ba = 0, n = A + B;
	string s;
	s.reserve(n);
	if (A < B)
	{
		ba = 'a' + 'b';
		std::swap(A, B);
	}

	while (A > 0 && B > 0)
	{
		if (A > B)
		{
			s.push_back('a');
			--A;
		}
		s.push_back('a');
		s.push_back('b');
		--A;
		--B;
	}
	while (A--)
		s.push_back('a');

	if (ba)
		for (int i = 0; i < n; ++i)
			s[i] = static_cast<char>(ba - s[i]);
	return s;
}


int main()
{
	OutString(strWithout3a3b(1, 2));
	OutString(strWithout3a3b(4, 1));
}
