#include "leetcode.hpp"

/* 784. 字母大小写全排列

给定一个字符串S，通过将字符串S中的每个字母转变大小写，我们可以获得一个新的字符串。
返回所有可能得到的字符串集合。

示例:
输入: S = "a1b2"
输出: ["a1b2", "a1B2", "A1b2", "A1B2"]

输入: S = "3z4"
输出: ["3z4", "3Z4"]

输入: S = "12345"
输出: ["12345"]

注意：
	S 的长度不超过12。
	S 仅由数字和字母组成。
*/


vector<string> letterCasePermutation(string S)
{
	vector<string> d;
	vector<int> aid;
	int t, len = static_cast<int>(S.size());

	for (int i = 0; i < len; ++i)
	{
		if (isalpha(S[i]))
			aid.emplace_back(i);
	}

	len = static_cast<int>(aid.size());
	t = 1 << len;
	d.resize(t, S);

	for (int i = 0; i < len; ++i)
	{
		int p = aid[i];
		int m = (1 << i);
		int c = tolower(S[p]);
		for (int n = 0; n < t; ++n)
			d[n][p] = static_cast<char>((n & m) ? c : toupper(c));
	}

	return d;
}

int main()
{
	output(letterCasePermutation("a1b2"), "\n", "Letter Case Permutation");
	output(letterCasePermutation("3z42"), "\n", "Letter Case Permutation");
	output(letterCasePermutation("1234"), "\n", "Letter Case Permutation");
}
