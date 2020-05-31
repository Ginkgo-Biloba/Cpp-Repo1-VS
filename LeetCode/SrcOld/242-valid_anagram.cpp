#include "leetcode.hpp"

/* 242. 有效的字母异位词

给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

示例 1:
输入: s = "anagram", t = "nagaram"
输出: true

示例 2:
输入: s = "rat", t = "car"
输出: false

说明:
你可以假设字符串只包含小写字母。

进阶:
如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
*/

bool isAnagram(string s, string t)
{
	size_t len = s.length();
	int num[128] = { 0 };
	if (len != t.length())
		return false;
	for (size_t i = 0; i < len; ++i)
	{
		num[s[i]] += 1;
		num[t[i]] -= 1;
	}
	for (int i = 0; i < 128; ++i)
	{
		if (num[i] != 0)
			return false;
	}
	return true;
}


int main()
{
	OutBool(isAnagram("anagram", "nagaram"));
	OutBool(isAnagram("rat", "car"));
	OutBool(isAnagram("", ""));
}
