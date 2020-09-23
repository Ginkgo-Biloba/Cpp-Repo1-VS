#include "leetcode.hpp"

/* 214. 最短回文串

给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。
找到并返回可以用这种方式转换的最短回文串。

示例 1:
输入: "aacecaaa"
输出: "aaacecaaa"

示例 2:
输入: "abcd"
输出: "dcbabcd"
*/

// https://leetcode.com/problems/shortest-palindrome/discuss/60099/AC-in-288-ms-simple-brute-force
// 抄的
string shortestPalindrome2(string s)
{
	int len = static_cast<int>(s.length());
	string t = s;
	reverse(t.begin(), t.end());
	for (int i = 0; i < len; ++i)
	{
		int k = len - i;
		// memcmp 比 strcmp 快
		if (!memcmp(t.data() + i, s.data(), k))
			return t.substr(0, i) + s;
	}
	return t + s;
}

// https://leetcode.com/problems/shortest-palindrome/discuss/60113/Clean-KMP-solution-with-super-detailed-explanation
// 抄的
string shortestPalindrome(string s)
{
	string t = s;
	std::reverse(t.begin(), t.end());
	string z = s + "#" + t;
	size_t len = z.size();
	// 这个表，第 i 位存的是普通 KMP 的第 i + 1 位
	vector<size_t> kmp(len, 0);
	for (size_t i = 1; i < len; ++i)
	{
		size_t k = kmp[i - 1u];
		while (k > 0 && z[i] != z[k])
			k = kmp[k - 1u];
		kmp[i] = k + (z[k] == z[i] ? 1 : 0);
	}
	z = t.substr(0, s.size() - kmp.back()) + s;
	return z;
}


int main()
{
	OutString(shortestPalindrome("aacecaaa"));
	OutString(shortestPalindrome("abcd"));
}
