#include "leetcode.hpp"

/* 76. 最小覆盖子串

给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。

示例：

输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"

说明：
	如果 S 中不存这样的子串，则返回空字符串 ""。
	如果 S 中存在这样的子串，我们保证它是唯一的答案。
*/

// https://leetcode.com/problems/minimum-window-substring/discuss/26808/Here-is-a-10-line-template-that-can-solve-most-'substring'-problems
// 抄的
string minWindow(string s, string t)
{
	int M[128] = { 0 };
	int count = static_cast<int>(t.length());
	int len = static_cast<int>(s.length());
	int start = 0, window = INT_MAX, h = 0, i, d;
	for (i = 0; i < count; ++i)
		M[t[i]] += 1;
	for (i = 0; i < len;)
	{
		d = s[i];
		M[d] -= 1;
		if (M[d] >= 0)
			--count;
		++i;
		if (count == 0)
		{
			while (count == 0)
			{
				d = s[h];
				if (M[d] == 0)
					++count;
				M[d] += 1;
				++h;
			}
			d = i - h + 1;
			if (d < window)
			{
				window = d;
				start = h - 1;
			}
		}
	}
	if (window == INT_MAX)
		window = 0;
	return s.substr(start, window);
}


int main()
{
	OutString(minWindow("ADOBECODEBANC", "ABC"));
	OutString(minWindow("ADOBECODEBANC", "ABZ"));
	OutString(minWindow("A", "A"));
	OutString(minWindow("A", "AA"));
}
