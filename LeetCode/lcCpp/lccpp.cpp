﻿#include "../srcOld/utility.hpp"

/* 336. 回文对

给定一组唯一的单词，找出所有不同的索引对(i, j)，使得列表中的两个单词 words[i] + words[j] 可拼接成回文串。

示例 1:
输入: ["abcd","dcba","lls","s","sssll"]
输出: [[0,1],[1,0],[3,2],[2,4]]
解释: 可拼接成的回文串为 ["dcbaabcd","abcddcba","slls","llssssll"]

示例 2:
输入: ["bat","tab","cat"]
输出: [[0,1],[1,0]]
解释: 可拼接成的回文串为 ["battab","tabbat"]
*/

// https://leetcode.com/problems/self-crossing/discuss/79140/Re-post%3A-2-O(N)-C%2B%2B-0ms-solutions
// 抄的
vector<vector<int>> palindromePairs(vector<string>& words)
{
	
}

int main()
{
	vector<string> words = { 2, 1, 1, 2 };
	vector<vector<int>> ans = palindromePairs(words);
	output(ans, "palindromePairs");
}
