#include "../srcOld/utility.hpp"

/* 387. 字符串中的第一个唯一字符

给定一个字符串，找到它的第一个不重复的字符，并返回它的索引。
如果不存在，则返回 -1。

案例:
s = "leetcode"
返回 0.

s = "loveleetcode",
返回 2.
*/

int firstUniqChar(string const& s)
{
	unsigned count[26] = { 0 };
	int len = static_cast<int>(s.size());
	for (int i = 0; i < len; ++i)
		++count[s[i] - 'a'];
	for (int i = 0; i < len; ++i)
		if (count[s[i] - 'a'] == 1U)
			return i;
	return -1;
}


int main()
{
	int d = firstUniqChar(string("leetcode"));
	printf("firstUniqChar: %d\n", d);
}
