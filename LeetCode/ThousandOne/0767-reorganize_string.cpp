#include "leetcode.hpp"

/* 767. 重构字符串

给定一个字符串S，检查是否能重新排布其中的字母，使得两相邻的字符不同。

若可行，输出任意可行的结果。若不可行，返回空字符串。

示例 1:
输入: S = "aab"
输出: "aba"

示例 2:
输入: S = "aaab"
输出: ""

注意:
	S 只包含小写字母并且长度在[1, 500]区间内。
*/

// https://leetcode.com/problems/reorganize-string/discuss/232469/Java-No-Sort-O(N)-0ms-beat-100
// 抄的
string reorganizeString(string S)
{
	string D;
	int len = static_cast<int>(S.size());
	int cnt[26] = { 0 };
	int maxcnt = 0, maxch = '\0';

	for (int i = 0; i < len; ++i)
		++cnt[S[i] - 'a'];
	for (int i = 0; i < 26; ++i)
		if (cnt[i] > maxcnt)
		{
			maxcnt = cnt[i];
			maxch = i;
		}
	if (2 * maxcnt - 1 > len)
		return D;

	D = S;
	int pos = 0;
	while (cnt[maxch])
	{
		D[pos] = static_cast<char>(maxch);
		pos += 2;
		--cnt[maxch];
	}
	for (int i = 0; i < 26; ++i)
		while (cnt[i] > 0)
		{
			if (pos >= len)
				pos = 1;
			D[pos] = static_cast<char>(i);
			pos += 2;
			--cnt[i];
		}

	for (int i = 0; i < len; ++i)
		D[i] = static_cast<char>(D[i] + 'a');
	return D;
}


int main()
{
	OutExpr(reorganizeString("aab").c_str(), "%s");
	OutExpr(reorganizeString("aaab").c_str(), "%s");
	OutExpr(reorganizeString("vvvlo").c_str(), "%s");
}
