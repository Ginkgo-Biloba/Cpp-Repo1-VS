#include "leetcode.hpp"

/* 1081. 不同字符的最小子序列

返回字符串 text 中按字典序排列最小的子序列，该子序列包含 text 中所有不同字符一次。

示例 1：
输入："cdadabcc"
输出："adbc"

示例 2：
输入："abcd"
输出："abcd"

示例 3：
输入："ecbacba"
输出："eacb"

示例 4：
输入："leetcode"
输出："letcod"

提示：
	1 <= text.length <= 1000
	text 由小写英文字母组成

注意：本题目与 316 https://leetcode-cn.com/problems/remove-duplicate-letters/ 相同
*/

// https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/discuss/308210/JavaC%2B%2BPython-Stack-Solution-O(N)
// 抄的
string smallestSubsequence(string S)
{
	int len = static_cast<int>(S.size());
	string A;
	int last[26] = { 0 }, seen[26] = { 0 };
	int ch = 'a';

	for (int i = 0; i < len; ++i)
		last[S[i] - ch] = i;
	for (int i = 0; i < len; ++i)
	{
		seen[S[i] - ch] += 1;
		if (seen[S[i] - ch] > 1)
			continue;
		while (!A.empty()
		&& A.back() > S[i]
		&& i < last[A.back() - ch])
		{
			seen[A.back() - ch] = 0;
			A.pop_back();
		}
		A.push_back(S[i]);
	}
	return A;
}


int main()
{
	OutString(smallestSubsequence("cdadabcc"));
	OutString(smallestSubsequence("abcd"));
	OutString(smallestSubsequence("ecbacba"));
	OutString(smallestSubsequence("leetcode"));
}
