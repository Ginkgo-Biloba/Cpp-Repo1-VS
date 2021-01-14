#include "leetcode.hpp"

/* 1717. 删除子字符串的最大得分

给你一个字符串 s 和两个整数 x 和 y 。
你可以执行下面两种操作任意次。
	删除子字符串 "ab" 并得到 x 分。
		比方说，从 "cabxbae" 删除 ab ，得到 "cxbae" 。
	删除子字符串"ba" 并得到 y 分。
		比方说，从 "cabxbae" 删除 ba ，得到 "cabxe" 。

请返回对 s 字符串执行上面操作若干次能得到的最大得分。

示例 1：
输入：s = "cdbcbbaaabab", x = 4, y = 5
输出：19
解释：
- 删除 "cdbcbbaaabab" 中加粗的 "ba" ，得到 s = "cdbcbbaaab" ，加 5 分。
- 删除 "cdbcbbaaab" 中加粗的 "ab" ，得到 s = "cdbcbbaa" ，加 4 分。
- 删除 "cdbcbbaa" 中加粗的 "ba" ，得到 s = "cdbcba" ，加 5 分。
- 删除 "cdbcba" 中加粗的 "ba" ，得到 s = "cdbc" ，加 5 分。
总得分为 5 + 4 + 5 + 5 = 19 。

示例 2：
输入：s = "aabbaaxybbaabb", x = 5, y = 4
输出：20

提示：
	1 <= s.length <= 10^5
	1 <= x, y <= 10^4
	s 只包含小写英文字母。
*/

int maximumGain(string s, int x, int y)
{
	int sum = 0;
	int len = static_cast<int>(s.size());
	char a = 'a', b = 'b';
	string t;
	if (x < y)
	{
		std::swap(x, y);
		std::swap(a, b);
	}
	for (int i = 0; i < len; ++i)
	{
		if (s[i] != b || t.empty() || t.back() != a)
			t.push_back(s[i]);
		else
		{
			t.pop_back();
			sum += x;
		}
	}
	t.swap(s);
	t.clear();
	len = static_cast<int>(s.size());
	for (int i = 0; i < len; ++i)
	{
		if (s[i] != a || t.empty() || t.back() != b)
			t.push_back(s[i]);
		else
		{
			t.pop_back();
			sum += y;
		}
	}
	return sum;
}


int main()
{
	OutExpr(maximumGain("cdbcbbaaabab", 4, 5), "%d");
	OutExpr(maximumGain("aabbaaxybbaabb", 5, 4), "%d");
}
