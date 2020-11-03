#include "leetcode.hpp"

/* 1638. 统计只差一个字符的子串数目

给你两个字符串 s 和 t ，请你找出 s 中的非空子串的数目，这些子串满足替换 一个不同字符 以后，是 t 串的子串。
换言之，请你找到 s 和 t 串中 恰好 只有一个字符不同的子字符串对的数目。

比方说， "[compute]r" 和 "[computa]tion" 加粗部分只有一个字符不同： 'e'/'a' ，所以这一对子字符串会给答案加 1 。

请你返回满足上述条件的不同子字符串对数目。

一个 子字符串 是一个字符串中连续的字符。

示例 1：
输入：s = "aba", t = "baba"
输出：6
解释：以下为只相差 1 个字符的 s 和 t 串的子字符串对：
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
加粗部分分别表示 s 和 t 串选出来的子字符串。

示例 2：
输入：s = "ab", t = "bb"
输出：3
解释：以下为只相差 1 个字符的 s 和 t 串的子字符串对：
("ab", "bb")
("ab", "bb")
("ab", "bb")
加粗部分分别表示 s 和 t 串选出来的子字符串。

示例 3：
输入：s = "a", t = "a"
输出：0

示例 4：
输入：s = "abe", t = "bbc"
输出：10

提示：
	1 <= s.length, t.length <= 100
	s 和 t 都只包含小写英文字母。
*/

class Solution
{
	// https://leetcode.com/problems/count-substrings-that-differ-by-one-character/discuss/917985/JavaC%2B%2BPython-Time-O(nm)-Space-O(1)
	// 抄的
	int count(string const& s, string const& t, size_t i, size_t k)
	{
		int sum = 0, pre = 0, cur = 0;
		size_t m = s.size(), n = t.size();
		for (; i < m && k < n; ++i, ++k)
		{
			++cur;
			if (s[i] != t[k])
			{
				pre = cur;
				cur = 0;
			}
			sum += pre;
		}
		return sum;
	}

public:
	int countSubstrings(string s, string t)
	{
		int sum = 0;
		for (size_t i = s.size() - 1; i != (size_t)(-1); --i)
			sum += count(s, t, i, 0);
		// (0,0) 上面已经计数过了
		for (size_t i = t.size() - 1; i > 0; --i)
			sum += count(s, t, 0, i);
		return sum;
	}

	int countSubstrings0(string s, string t)
	{
		int m = static_cast<int>(s.size());
		int n = static_cast<int>(t.size());
		int ans = 0;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
			{
				int d = 0, e = min(m - i, n - j);
				for (int k = 0; (k < e) && (d < 2); ++k)
				{
					d += s[i + k] != t[j + k];
					ans += d == 1;
				}
			}
		return ans;
	}
};


int main()
{
	Solution s;
	OutExpr(s.countSubstrings("aba", "baba"), "%d");
	OutExpr(s.countSubstrings("ab", "bb"), "%d");
	OutExpr(s.countSubstrings("a", "a"), "%d");
	OutExpr(s.countSubstrings("abe", "bbc"), "%d");
}
