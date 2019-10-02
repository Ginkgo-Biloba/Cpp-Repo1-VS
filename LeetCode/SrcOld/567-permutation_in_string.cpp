#include "leetcode.hpp"

/* 567. 字符串的排列

给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。
换句话说，第一个字符串的排列之一是第二个字符串的子串。

示例1:
输入: s1 = "ab" s2 = "eidbaooo"
输出: True
解释: s2 包含 s1 的排列之一 ("ba").

示例2:
输入: s1= "ab" s2 = "eidboaoo"
输出: False

注意：
	输入的字符串只包含小写字母
	两个字符串的长度都在 [1, 10,000] 之间
*/

bool checkInclusion(string s1, string s2)
{
	int len1 = static_cast<int>(s1.size());
	int len2 = static_cast<int>(s2.size());
	int i = 0;
	int h1[52], *h2 = h1 + 26;
	if (len1 > len2)
		return false;

	memset(h1, 0, sizeof(h1));
	for (i = 0; i != len1 - 1; ++i)
	{
		++h1[s1[i] - 'a'];
		++h2[s2[i] - 'a'];
	}
	++h1[s1[len1 - 1] - 'a'];
	for (; i != len2; ++i)
	{
		++h2[s2[i] - 'a'];
		bool b = true;
		for (int c = 0; c < 26; ++c)
			if (h1[c] != h2[c])
			{
				b = false;
				break;
			}
		if (b)
			return true;
		--h2[s2[i - len1 + 1] - 'a'];
	}
	return false;
}


int main()
{
	OutExpr(boolstr[checkInclusion("ab", "eidbaooo")], "%s");
}
