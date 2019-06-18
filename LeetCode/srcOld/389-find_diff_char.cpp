#include "../srcOld/utility.hpp"

/* 389. 找不同

给定两个字符串 s 和 t，它们只包含小写字母。
字符串 t 由字符串 s 随机重排，然后在随机位置添加一个字母。
请找出在 t 中被添加的字母。

示例:
输入：
s = "abcd"
t = "abcde"
输出：
e
解释：
'e' 是那个被添加的字母。
*/

char findTheDifference(string s, string t)
{
	char c = '\0';
	int slen = static_cast<int>(s.size());

	for (int i = 0; i < slen; ++i)
		c ^= s[i];
	for (int i = 0; i <= slen; ++i)
		c ^= t[i];

	return c;
}


int main()
{
	string a = "abcd";
	string b = "abcde";
	char d = findTheDifference(a, b);
	printf("firstUniqChar: %c\n", d);
}
