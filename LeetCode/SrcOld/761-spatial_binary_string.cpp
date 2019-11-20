#include "leetcode.hpp"

/* 761. 特殊的二进制序列

特殊的二进制序列是具有以下两个性质的二进制序列：
	0 的数量与 1 的数量相等。
	二进制序列的每一个前缀码中 1 的数量要大于等于 0 的数量。

给定一个特殊的二进制序列 S，以字符串形式表示。
定义一个操作 为首先选择 S 的两个连续且非空的特殊的子串，然后将它们交换。
两个子串为连续的当且仅当第一个子串的最后一个字符恰好为第二个子串的第一个字符的前一个字符。

在任意次数的操作之后，交换后的字符串按照字典序排列的最大的结果是什么？

示例 1:
输入: S = "11011000"
输出: "11100100"
解释:
将子串 "10" （在S[1]出现） 和 "1100" （在S[3]出现）进行交换。
这是在进行若干次操作后按字典序排列最大的结果。

说明:
	S 的长度不超过 50。
	S 保证为一个满足上述定义的特殊的二进制序列。
*/

// https://leetcode.com/problems/special-binary-string/discuss/113211/JavaC%2B%2BPython-Easy-and-Concise-Recursion
// 抄的
string makeLargestSpecial(string const& S)
{
	int count = 0, i = 0;
	int len = static_cast<int>(S.size());
	string D;
	vector<string> seg;
	for (int k = 0; k < len; ++k)
	{
		if (S[k] == '1')
			++count;
		else
			--count;
		if (count == 0)
		{
			seg.push_back("1"
				+ makeLargestSpecial(S.substr(i + 1, k - i - 1))
				+ "0");
			i = k + 1;
		}
	}
	sort(seg.begin(), seg.end(), std::greater<string>());
	D.reserve(len);
	for (string const& s : seg)
		D += s;
	return D;
}


int main()
{
	OutExpr(
		makeLargestSpecial("11011000").c_str(),
		"%s");
}
