#include "leetcode.hpp"

/* 345. 反转字符串中的元音字母

编写一个函数，以字符串作为输入，反转该字符串中的元音字母。

示例 1:
输入: "hello"
输出: "holle"

示例 2:
输入: "leetcode"
输出: "leotcede"

说明:
元音字母不包含字母"y"。
*/

bool isvowel(int c)
{
	c = tolower(c);
	return false
		|| c == 'a' || c == 'e'
		|| c == 'i' || c == 'o'
		|| c == 'u';
}

string reverseVowels(string s)
{
	auto a = s.begin(), b = s.end();
	if (a == b)
		return s;
	for (--b; a < b; ++a, --b)
	{
		while (a < b && !isvowel(*a)) ++a;
		while (a < b && !isvowel(*b)) --b;
		if (a < b)
			iter_swap(a, b);
	}
	return s;
}


int main()
{}
