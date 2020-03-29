#include "leetcode.hpp"

/* 1156. 单字符重复子串的最大长度

如果字符串中的所有字符都相同，那么这个字符串是单字符重复的字符串。

给你一个字符串 text，你只能交换其中两个字符一次或者什么都不做，然后得到一些单字符重复的子串。
返回其中最长的子串的长度。

示例 1：
输入：text = "ababa"
输出：3

示例 2：
输入：text = "aaabaaa"
输出：6

示例 3：
输入：text = "aaabbaaa"
输出：4

示例 4：
输入：text = "aaaaa"
输出：5

示例 5：
输入：text = "abcdef"
输出：1

提示：
	1 <= text.length <= 20000
	text 仅由小写英文字母组成。
*/

int maxRepOpt1(string T)
{
	int len = static_cast<int>(T.size());
	vector<pair<int, int>> C;
	int count[26] = { 0 };
	int h = 0, i = 0, num = 1;

	C.reserve(len);
	for (i = 0; i < len; ++i)
	{
		++(count[T[i] - 'a']);
		if (T[i] != T[h])
		{
			C.push_back({ T[h] - 'a', i - h });
			h = i;
		}
	}
	C.push_back({ T[h] - 'a', len - h });

	len = static_cast<int>(C.size());
	for (i = 0; i < len; ++i)
		num = max(num, min(C[i].second + 1, count[C[i].first]));
	for (i = 2; i < len; ++i)
		if (C[i - 2].first == C[i].first && C[i - 1].second == 1)
		{
			num = max(num,
			 min(C[i - 2].second + C[i].second + 1, count[C[i].first]));
		}

	return num;
}


int main()
{
	OutExpr(maxRepOpt1("ababa"), "%d");
	OutExpr(maxRepOpt1("aaabaaa"), "%d");
	OutExpr(maxRepOpt1("aaabbaaa"), "%d");
	OutExpr(maxRepOpt1("aaaaa"), "%d");
	OutExpr(maxRepOpt1("abcdef"), "%d");
}
