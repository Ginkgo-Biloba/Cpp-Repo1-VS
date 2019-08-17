#include "leetcode.hpp"

/* 451. 根据字符出现频率排序

给定一个字符串，请将字符串里的字符按照出现的频率降序排列。

示例 1:
输入:
"tree"
输出:
"eert"
解释:
'e'出现两次，'r'和't'都只出现一次。
因此'e'必须出现在'r'和't'之前。此外，"eetr"也是一个有效的答案。

示例 2:
输入:
"cccaaa"
输出:
"cccaaa"
解释:
'c'和'a'都出现三次。此外，"aaaccc"也是有效的答案。
注意"cacaca"是不正确的，因为相同的字母必须放在一起。

示例 3:
输入:
"Aabb"
输出:
"bbAa"
解释:
此外，"bbaA"也是一个有效的答案，但"Aabb"是不正确的。
注意'A'和'a'被认为是两种不同的字符。
*/

string frequencySort(string& s)
{
	typedef pair<int, int> pairint;
	pairint hist[128];
	memset(hist, 0, sizeof(hist));
	size_t len = s.size();

	for (int n = 0; n < 128; ++n)
		hist[n] = pairint(n, 0);
	for (size_t i = 0; i < len; ++i)
		++(hist[static_cast<int>(s[i])].second);
	std::sort(hist, hist + 128,
		[](pairint const& x, pairint const& y)
	{
		return x.second > y.second;
	});

	len = 0;
	for (int n = 0; n < 128; ++n)
	{
		char c = static_cast<char>(hist[n].first);
		int i = hist[n].second;
		if (i == 0)
			break;
		for (; i; --i, ++len)
			s[len] = c;
	}

	return s;
}


int main()
{
	string s("tree");
	OutExpr(frequencySort(s).c_str(), "%s");
}
