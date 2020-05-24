#include "leetcode.hpp"

/* 125. 验证回文串

给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。

示例 1:
输入: "A man, a plan, a canal: Panama"
输出: true

示例 2:
输入: "race a car"
输出: false
*/

bool isPalindrome(string s)
{
	int len = static_cast<int>(s.length());
	int a = 0, b = len - 1;
	for (; a < b; ++a, --b)
	{
		while ((a < b) && !isalnum(s[a]))
			++a;
		while ((a < b) && !isalnum(s[b]))
			--b;
		if (tolower(s[a]) != tolower(s[b]))
			return false;
	}
	return true;
}


int main()
{
	OutBool(isPalindrome("A man, a plan, a canal: Panama"));
	OutBool(isPalindrome("race a car"));
}
