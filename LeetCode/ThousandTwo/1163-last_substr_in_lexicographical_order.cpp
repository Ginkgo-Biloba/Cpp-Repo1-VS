#include "leetcode.hpp"

/* 1163. 按字典序排在最后的子串

给你一个字符串 s，找出它的所有子串并按字典序排列，返回排在最后的那个子串。

示例 1：
输入："abab"
输出："bab"
解释：我们可以找出 7 个子串 ["a", "ab", "aba", "abab", "b", "ba", "bab"]。按字典序排在最后的子串是 "bab"。

示例 2：
输入："leetcode"
输出："tcode"

提示：
	1 <= s.length <= 4 * 10^5
	s 仅含有小写英文字符。
*/

class Solution1
{
	typedef pair<string, int> psi;

	struct MyComp
	{
		bool operator()(psi const& a, psi const& b) const
		{
			size_t A = a.first.size(), B = b.first.size();
			int r = strcmp(a.first.c_str(), b.first.c_str());
			return (r != 0) ? (r > 0) : (A > B);
		}
	};

public:
	string lastSubstring(string S)
	{
		MyComp mycomp;
		int len = static_cast<int>(S.size());
		char maxch = 0;
		vector<int> pos;
		for (int i = 0; i < len; ++i)
		{
			if (S[i] > maxch)
			{
				maxch = S[i];
				pos.clear();
			}
			if (S[i] == maxch)
				pos.push_back(i);
		}
		if (len == 1 || maxch == 'a')
			return S;

		pair<string, int> cur;
		vector<pair<string, int>> cand;
		cur.first.push_back(maxch);
		for (int i : pos)
		{
			cur.second = i + 1;
			cand.push_back(cur);
		}

		size_t size = cand.size();
		while (size > 1)
		{
			for (size_t i = 0; i < size; ++i)
				if (cand[i].second < len)
				{
					cand[i].first.push_back(S[cand[i].second]);
					++(cand[i].second);
				}

			sort(cand.begin(), cand.end(), mycomp);
			cur = cand[0];
			for (size_t i = size - 1; i != 0; --i)
			{
				if (cand[i].first < cur.first)
					cand.pop_back();
			}
			size = cand.size();
		}

		cur = cand[0];
		for (int i = cur.second; i < len; ++i)
			cur.first.push_back(S[i]);
		return cur.first;
	}
};

// https://leetcode.com/problems/last-substring-in-lexicographical-order/discuss/363662/Short-python-code-O(n)-time-and-O(1)-space-with-proof-and-visualization
// 抄的
class Solution
{
public:
	string lastSubstring(string s)
	{
		int n = static_cast<int>(s.size());
		int i = 0, j = 1, k = 0;
		while (j + k < n)
		{
			if (s[i + k] == s[j + k])
			{
				++k;
				continue;
			}
			if (s[i + k] > s[j + k])
				j = j + k + 1;
			else
			{
				i = max(i + k + 1, j);
				j = i + 1;
			}
			k = 0;
		}
		return s.substr(i);
	}
};


int main()
{
	Solution s;
	OutString(s.lastSubstring("abab"));
	OutString(s.lastSubstring("leetcode"));
	OutString(s.lastSubstring("leetcodeleetcode"));
}
