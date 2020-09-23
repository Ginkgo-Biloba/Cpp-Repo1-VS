#include "leetcode.hpp"

/* 336. 回文对

给定一组唯一的单词，找出所有不同 的索引对(i, j)，使得列表中的两个单词，words[i] + words[j] ，可拼接成回文串。

示例 1:
输入: ["abcd","dcba","lls","s","sssll"]
输出: [[0,1],[1,0],[3,2],[2,4]]
解释: 可拼接成的回文串为 ["dcbaabcd","abcddcba","slls","llssssll"]

示例 2:
输入: ["bat","tab","cat"]
输出: [[0,1],[1,0]]
解释: 可拼接成的回文串为 ["battab","tabbat"]
*/

// https://leetcode.com/problems/palindrome-pairs/discuss/79215/Easy-to-understand-AC-C%2B%2B-solution-O(n*k2)-using-map
// 抄的，假定没有相同的字符串
class Solution
{
	bool isPalindrome(string str)
	{
		int i = 0;
		int j = static_cast<int>(str.length()) - 1;
		while (i < j)
		{
			if (str[i++] != str[j--])
				return false;
		}
		return true;
	}

public:
	vector<vector<int>> palindromePairs(vector<string>& words)
	{
		unordered_map<string, int> dict;
		vector<vector<int>> ans;
		int len = static_cast<int>(words.size());
		int iEmpty = -1;

		for (int i = 0; i < len; ++i)
		{
			string key = words[i];
			if (key.empty())
				iEmpty = i;
			reverse(key.begin(), key.end());
			dict[key] = i;
		}

		// 如果 空字符串 "" 存在，连接所有单词为 ("", word)
		if (iEmpty >= 0)
			for (int i = 0; i < len; ++i)
			{
				if (i != iEmpty && isPalindrome(words[i]))
					ans.push_back({ iEmpty, i });
			}

		for (int i = 0; i < len; ++i)
		{
			int ilen = static_cast<int>(words[i].length());
			for (int k = 0; k < ilen; ++k)
			{
				string left = words[i].substr(0, k);
				string right = words[i].substr(k, ilen - k);

				// dict 里面有空字符串，这里面包含了 (word, "")
				auto it = dict.find(left);
				if (it != dict.end() && isPalindrome(right))
					ans.push_back({ i, it->second });

				it = dict.find(right);
				if (it != dict.end() && isPalindrome(left) && it->second != i)
					ans.push_back({ it->second, i });
			}
		}

		return ans;
	}
};


int main()
{
	vector<string>
		a = { "abcd", "dcba", "lls", "s", "sssll" },
		b = { "bat", "tab", "cat" };
	Solution s;
	output(s.palindromePairs(a), "Palindrome Pairs");
	output(s.palindromePairs(b), "Palindrome Pairs");
}
