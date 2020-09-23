#include "leetcode.hpp"

/* 820. 单词的压缩编码

给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A。

例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示为 S = "time#bell#" 和 indexes = [0, 2, 5]。

对于每一个索引，我们可以通过从字符串 S 中索引的位置开始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。

那么成功对给定单词列表进行编码的最小字符串长度是多少呢？

示例：
输入: words = ["time", "me", "bell"]
输出: 10
说明: S = "time#bell#" ， indexes = [0, 2, 5] 。

提示：
	1 <= words.length <= 2000
	1 <= words[i].length <= 7
	每个单词都是小写字母 。
*/


int minimumLengthEncoding(vector<string>& words)
{
	int len = static_cast<int>(words.size());
	int ans = 0;

	for (int i = 0; i < len; ++i)
		reverse(words[i].begin(), words[i].end());

	sort(words.begin(), words.end());

	for (int i = 1; i < len; ++i)
	{
		size_t s0 = words[i - 1].size();
		size_t s1 = words[i].size();
		if ((s0 > s1)
			|| strncmp(words[i - 1].data(), words[i].data(), s0))
			ans += static_cast<int>(s0) + 1;
	}
	ans += static_cast<int>(words[len - 1].size()) + 1;

	return ans;
}


int main()
{
	vector<string> w = { "time", "me", "bell" };
	OutExpr(minimumLengthEncoding(w), "%d");
}
