#include "leetcode.hpp"

/* 583. 两个字符串的删除操作

给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

示例 1:
输入: "sea", "eat"
输出: 2
解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"

说明:
	给定单词的长度不超过500。
	给定单词中的字符只含有小写字母。
*/

int minDistance(string word1, string word2)
{
	int len1 = static_cast<int>(word1.size());
	int len2 = static_cast<int>(word2.size());
	if (len1 == 0 || len2 == 0)
		return len1 + len2;

	auto at = [len2](int y, int x) -> int { return y * (len2 + 1) + x; };
	unique_ptr<int[]> dp(new int[(len1 + 1) * (len2 + 1)]);
	memset(dp.get(), 0, (len1 + 1) * (len2 + 1) * sizeof(int));

	for (int i = 1; i <= len1; ++i)
		for (int k = 1; k <= len2; ++k)
		{
			if (word1[i - 1] == word2[k - 1])
				dp[at(i, k)] = dp[at(i - 1, k - 1)] + 1;
			else
				dp[at(i, k)] = std::max(
					dp[at(i - 1, k)], dp[at(i, k - 1)]);
		}
	return len1 + len2 - 2 * dp[at(len1, len2)];
}


int main()
{
	OutExpr(minDistance("sea", "eat"), "%d");
}
