#include "leetcode.hpp"

/* 844. 比较含退格的字符串

给定 S 和 T 两个字符串，当它们分别被输入到空白的文本编辑器后，判断二者是否相等，并返回结果。
# 代表退格字符。

示例 1：
输入：S = "ab#c", T = "ad#c"
输出：true
解释：S 和 T 都会变成 “ac”。

示例 2：
输入：S = "ab##", T = "c#d#"
输出：true
解释：S 和 T 都会变成 “”。

示例 3：
输入：S = "a##c", T = "#a#c"
输出：true
解释：S 和 T 都会变成 “c”。

示例 4：
输入：S = "a#c", T = "b"
输出：false
解释：S 会变成 “c”，但 T 仍然是 “b”。

提示：
	1 <= S.length <= 200
	1 <= T.length <= 200
	S 和 T 只含有小写字母以及字符 '#'。

Follow up:
	Can you solve it in O(N) time and O(1) space?
*/

bool backspaceCompare(string S, string T)
{
	int is = 0, slen = static_cast<int>(S.size());
	int it = 0, tlen = static_cast<int>(T.size());

	for (int i = 0; i < slen; ++i)
	{
		if (S[i] != '#')
			S[is++] = S[i];
		else if (is > 0)
			--is;
	}
	for (int i = 0; i < tlen; ++i)
	{
		if (T[i] != '#')
			T[it++] = T[i];
		else if (it > 0)
			--it;
	}

	return (is == it)
		&& !strncmp(S.data(), T.data(), is);
}


int main()
{
	OutBool(backspaceCompare("ab#c", "ad#c"));
	OutBool(backspaceCompare("ab##", "c#d#"));
	OutBool(backspaceCompare("a##c", "#a#c"));
	OutBool(backspaceCompare("a#c", "b"));
}
