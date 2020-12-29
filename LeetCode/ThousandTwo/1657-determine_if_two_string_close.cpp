#include "leetcode.hpp"

/* 1657. 确定两个字符串是否接近

如果可以使用以下操作从一个字符串得到另一个字符串，则认为两个字符串 接近 ：
	操作 1：交换任意两个 现有 字符。
		例如，abcde -> aecdb
	操作 2：将一个 现有 字符的每次出现转换为另一个 现有 字符，并对另一个字符执行相同的操作。
		例如，aacabb -> bbcbaa（所有 a 转化为 b ，而所有的 b 转换为 a ）

你可以根据需要对任意一个字符串多次使用这两种操作。

给你两个字符串，word1 和 word2 。
如果 word1 和 word2 接近 ，就返回 true ；否则，返回 false 。

示例 1：
输入：word1 = "abc", word2 = "bca"
输出：true
解释：2 次操作从 word1 获得 word2 。
执行操作 1："abc" -> "acb"
执行操作 1："acb" -> "bca"

示例 2：
输入：word1 = "a", word2 = "aa"
输出：false
解释：不管执行多少次操作，都无法从 word1 得到 word2 ，反之亦然。

示例 3：
输入：word1 = "cabbba", word2 = "abbccc"
输出：true
解释：3 次操作从 word1 获得 word2 。
执行操作 1："cabbba" -> "caabbb"
执行操作 2："caabbb" -> "baaccc"
执行操作 2："baaccc" -> "abbccc"

示例 4：
输入：word1 = "cabbba", word2 = "aabbss"
输出：false
解释：不管执行多少次操作，都无法从 word1 得到 word2 ，反之亦然。

提示：
	1 <= word1.length, word2.length <= 10^5
	word1 和 word2 仅包含小写英文字母
*/

bool closeStrings(string A, string B)
{
	if (A.size() != B.size())
		return false;
	int n = static_cast<int>(A.size());
	int C[26] = { 0 }, D[26] = { 0 };
	int mc = 0, md = 0;
	for (int i = 0; i < n; ++i)
	{
		int a = A[i] - 'a';
		int b = B[i] - 'a';
		++C[a];
		++D[b];
		mc |= 1 << a;
		md |= 1 << b;
	}
	if (mc != md)
		return false;
	for (int i = 0; i < 26; ++i)
	{
		if (C[i] == 0)
			continue;
		for (int k = 0; k < 26; ++k)
			if (C[i] == D[k])
			{
				C[i] = D[k] = 0;
				break;
			}
		if (C[i])
			return false;
	}
	return true;
}


int main()
{
	OutBool(closeStrings("abc", "bca"));
	OutBool(closeStrings("a", "aa"));
	OutBool(closeStrings("cabbba", "abbccc"));
	OutBool(closeStrings("cabbba", "aabbss"));
	OutBool(closeStrings("uau", "ssx"));
}
