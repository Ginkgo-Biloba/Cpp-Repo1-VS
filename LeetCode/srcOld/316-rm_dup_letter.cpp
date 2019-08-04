#include "leetcode.hpp"

/* 316. 去除重复字母
 * 给定一个仅包含小写字母的字符串，去除字符串中重复的字母，使得每个字母只出现一次。
 * 需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
 */

 // https://leetcode.com/problems/remove-duplicate-letters/discuss/76767/C%2B%2B-simple-solution-easy-understanding
 // 抄的
string removeDuplicateLetters(string const& s)
{
	size_t const len = s.length();
	int cand[256] = { 0 };
	char visited[256] = { 0 };
	for (size_t i = 0; i < len; ++i)
		++(cand[s[i]]);
	string result = "0";
	for (size_t i = 0; i < len; ++i)
	{
		char c = s[i];
		--(cand[c]);
		if (visited[c]) continue;
		while (c < result.back() && cand[result.back()])
		{
			visited[result.back()] = 0;
			result.pop_back();
		}
		result.push_back(c);
		visited[c] = 1;
	}

	std::reverse(result.begin(), result.end());
	result.pop_back();
	std::reverse(result.begin(), result.end());
	return result;
}


int main()
{
	string str("bcabc");
	string ans = removeDuplicateLetters(str);
	printf("removeDuplicateLetters (%s): %s\n", str.c_str(), ans.c_str());
}

