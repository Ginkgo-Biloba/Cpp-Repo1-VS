#include "leetcode.hpp"

/* 139. 单词拆分

给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：
	拆分时可以重复使用字典中的单词。
	你可以假设字典中没有重复的单词。

示例 1：
输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。

示例 2：
输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释:
返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
注意你可以重复使用字典中的单词。

示例 3：
输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false
*/


// https://leetcode.com/problems/word-break/discuss/43814/C%2B%2B-Dynamic-Programming-simple-and-fast-solution-(4ms)-with-optimization
// 抄的
bool wordBreak(string s, vector<string>& wordDict)
{
	int len = static_cast<int>(s.length());
	unordered_set<string> S(wordDict.begin(), wordDict.end());
	vector<char> dp(len + 1);
	dp[0] = 1;
	for (int i = 1; i <= len; ++i)
		for (int h = i - 1; h >= 0; --h)
		{
			if (dp[h])
				if (S.find(s.substr(h, i - h)) != S.end())
				{
					dp[i] = 1;
					break;
				}
		}
	return dp[len] != 0;
}


int main()
{
	vector<string>
		a = { "leet", "code" },
		b = { "apple", "pen" },
		c = { "cats", "dog", "sand", "and", "cat" };
	OutBool(wordBreak("leetcode", a));
	OutBool(wordBreak("applepenapple", b));
	OutBool(wordBreak("catsandog", c));
}
