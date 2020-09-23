#include "leetcode.hpp"

/* 1593. 拆分字符串使唯一子字符串的数目最大

给你一个字符串 s ，请你拆分该字符串，并返回拆分后唯一子字符串的最大数目。

字符串 s 拆分后可以得到若干 非空子字符串 ，这些子字符串连接后应当能够还原为原字符串。
但是拆分出来的每个子字符串都必须是 唯一的 。

注意：子字符串 是字符串中的一个连续字符序列。

示例 1：
输入：s = "ababccc"
输出：5
解释：一种最大拆分方法为 ['a', 'b', 'ab', 'c', 'cc'] 。像 ['a', 'b', 'a', 'b', 'c', 'cc'] 这样拆分不满足题目要求，因为其中的 'a' 和 'b' 都出现了不止一次。

示例 2：
输入：s = "aba"
输出：2
解释：一种最大拆分方法为 ['a', 'ba'] 。

示例 3：
输入：s = "aa"
输出：1
解释：无法进一步拆分字符串。

提示：
	1 <= s.length <= 16
	s 仅包含小写英文字母
*/


class Solution
{
	int idxmap[16 * 16];
	char has[16 * 16];
	string s;
	int len, ans;

	unsigned popcnt(unsigned n)
	{
#if defined _MSC_VER
		return __popcnt(n);
#elif defined __GNUC__
		return __builtin_popcount(n);
#else
		n = n - ((n >> 1) & 0x55555555);
		n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
		n = (n + (n >> 4)) & 0x0f0f0f0f;
		n = (n * 0x1010101) >> 24;
		return n;
#endif
	}

	void check(int bit)
	{
		// just a pre-check, can be deleted
		if (popcnt(bit) <= static_cast<unsigned>(ans))
			return;
		memset(has, 0, sizeof(has));
		int word = 0;
		int pre = 0;
		for (int i = 1; i <= len; ++i)
			if ((i == len) || ((1 << (i - 1)) & bit))
			{
				int f = pre * 16 + i - 1;
				int m = idxmap[f];
				if (has[m])
					return;
				else
				{
					++word;
					pre = i;
					has[m] = 1;
				}
			}
		ans = max(ans, word);
	}

public:
	int maxUniqueSplit(string t)
	{
		s = t;
		len = static_cast<int>(s.size());
		ans = 1;

		map<string, int> M[16];
		int bit = 0;
		for (int i = 0; i < len; ++i)
		{
			t.clear();
			for (int k = i; k < len; ++k)
			{
				int n = k - i;
				int f = i * 16 + k;
				t.push_back(s[k]);
				auto it = M[n].find(t);
				if (it != M[n].end())
					idxmap[f] = it->second;
				else
				{
					M[n][t] = bit;
					idxmap[f] = bit;
					++bit;
				}
			}
		}

		bit = (1 << (len - 1)) - 1;
		for (; bit > 0; --bit)
			check(bit);
		return ans;
	}
};


int main()
{
	Solution s;
	OutExpr(s.maxUniqueSplit("ababccc"), "%d");
	OutExpr(s.maxUniqueSplit("aba"), "%d");
	OutExpr(s.maxUniqueSplit("aa"), "%d");
}
