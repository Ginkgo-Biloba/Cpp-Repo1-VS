#include "leetcode.hpp"

/* 1071. 字符串的最大公因子

对于字符串 S 和 T，只有在 S = T + ... + T（T 与自身连接 1 次或多次）时，我们才认定 “T 能除尽 S”。

返回字符串 X，要求满足 X 能除尽 str1 且 X 能除尽 str2。

示例 1：
输入：str1 = "ABCABC", str2 = "ABC"
输出："ABC"

示例 2：
输入：str1 = "ABABAB", str2 = "ABAB"
输出："AB"

示例 3：
输入：str1 = "LEET", str2 = "CODE"
输出：""

提示：
	1 <= str1.length <= 1000
	1 <= str2.length <= 1000
	str1[i] 和 str2[i] 为大写英文字母
*/


string gcdOfStrings(string A, string B)
{
	int a = static_cast<int>(A.size());
	int b = static_cast<int>(B.size());
	int t = a % b;
	while (t)
	{
		a = b;
		b = t;
		t = a % b;
	}
	t = b;
	a = static_cast<int>(A.size());
	b = static_cast<int>(B.size());
	char const* p = A.data();
	char const* q = B.data();
	for (int i = t; i < a; i += t)
	{
		if (memcmp(p, p + i, t * sizeof(char)))
			t = a + b;
	}
	for (int i = 0; i < b; i += t)
	{
		if (memcmp(p, q + i, t * sizeof(char)))
			t = a + b;
	}
	if (t == a + b)
		t = 0;
	return A.substr(0, t);
}


int main()
{
	OutString(gcdOfStrings("ABCABC", "ABC"));
	OutString(gcdOfStrings("ABABAB", "ABAB"));
	OutString(gcdOfStrings("LEET", "CODE"));
}
