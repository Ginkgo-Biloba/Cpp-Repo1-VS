#include "leetcode.hpp"

/* 395. 至少有K个重复字符的最长子串

找到给定字符串（由小写字符组成）中的最长子串 T。
要求 T 中的每一字符出现次数都不少于 k 。输出 T 的长度。

示例 1:
输入:
s = "aaabb", k = 3
输出:
3
最长子串为 "aaa" ，其中 'a' 重复了 3 次。

示例 2:
输入:
s = "ababbc", k = 2
输出:
5
最长子串为 "ababb" ，其中 'a' 重复了 2 次， 'b' 重复了 3 次。
*/

// 如果一个字母出现次数少于 k 次，那么不能出现在结果字符串中
// 从它那里把字符串分开，对子串递归处理

int longestSubstring(string const& S, int k)
{
	int ans = 0;
	int len = static_cast<int>(S.size());
	if (len == 0)
		return 0;

	int count[26] = { 0 };
	for (int i = 0; i < len; ++i)
		count[S[i] - 'a'] += 1;

	vector<string> split;
	int left = 0, right = 0;
	for (; right < len; ++right)
		if (count[S[right] - 'a'] < k)
		{
			if (left < right)
				split.push_back(S.substr(left, right - left));
			left = right + 1;
		}

	if (left == 0)
		return len;

	if (left < len)
		split.push_back(S.substr(left));

	for (string const& ss : split)
		ans = std::max(ans, longestSubstring(ss, k));

	return ans;
}


int main()
{
	OutExpr(longestSubstring("aaabb", 0), "%d");
}
