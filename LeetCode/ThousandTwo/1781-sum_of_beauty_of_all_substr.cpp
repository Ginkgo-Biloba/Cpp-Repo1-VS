#include "leetcode.hpp"

/* 1781. 所有子字符串美丽值之和

一个字符串的 美丽值 定义为：出现频率最高字符与出现频率最低字符的出现次数之差。
	比方说，"abaacc" 的美丽值为 3 - 1 = 2 。

给你一个字符串 s ，请你返回它所有子字符串的 美丽值 之和。

示例 1：
输入：s = "aabcb"
输出：5
解释：美丽值不为零的字符串包括 ["aab","aabc","aabcb","abcb","bcb"] ，每一个字符串的美丽值都为 1 。

示例 2：
输入：s = "aabcbaa"
输出：17

提示：
	1 <= s.length <= 500
	s 只包含小写英文字母。
*/

int beautySum(string s)
{
	int len = static_cast<int>(s.size());
	int ans = 0;
	for (int i = 0; i < len; ++i)
	{
		int m[26] = { 0 };
		m[s[i] - 'a'] += 1;
		for (int j = i + 1; j < len; ++j)
		{
			m[s[j] - 'a'] += 1;
			int a = len, b = -1;
			for (int c = 0; c < 26; ++c)
			{
				if (m[c] == 0)
					continue;
				a = min(a, m[c]);
				b = max(b, m[c]);
			}
			ans += b - a;
		}
	}
	return ans;
}


int main()
{
	OutExpr(beautySum("aabcb"), "%d");
	OutExpr(beautySum("aabcbaa"), "%d");
}
