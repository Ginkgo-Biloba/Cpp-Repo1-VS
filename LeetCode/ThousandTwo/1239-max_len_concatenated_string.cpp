#include "leetcode.hpp"

/* 1239. 串联字符串的最大长度

给定一个字符串数组 arr，字符串 s 是将 arr 某一子序列字符串连接所得的字符串，如果 s 中的每一个字符都只出现过一次，那么它就是一个可行解。

请返回所有可行解 s 中最长长度。

示例 1：
输入：arr = ["un","iq","ue"]
输出：4
解释：所有可能的串联组合是 "","un","iq","ue","uniq" 和 "ique"，最大长度为 4。

示例 2：
输入：arr = ["cha","r","act","ers"]
输出：6
解释：可能的解答有 "chaers" 和 "acters"。

示例 3：
输入：arr = ["abcdefghijklmnopqrstuvwxyz"]
输出：26

提示：
	1 <= arr.length <= 16
	1 <= arr[i].length <= 26
	arr[i] 中只含有小写英文字母
*/

// https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/discuss/414172/PythonC%2B%2BJava-Set-Solution
// 抄的
class Solution
{
	int popcnt(unsigned v)
	{
		v = (v & UINT32_C(0x55555555)) + ((v >> 1) & UINT32_C(0x55555555));
		v = (v & UINT32_C(0x33333333)) + ((v >> 2) & UINT32_C(0x33333333));
		v = (v & UINT32_C(0x0f0f0f0f)) + ((v >> 4) & UINT32_C(0x0f0f0f0f));
		v = (v & UINT32_C(0x00ff00ff)) + ((v >> 8) & UINT32_C(0x00ff00ff));
		v = (v & UINT32_C(0x0000ffff)) + ((v >> 16) & UINT32_C(0x0000ffff));
		return static_cast<int>(v);
	}

public:
	int maxLength(vector<string>& arr)
	{
		vector<int> dp(1);
		int ans = 0;
		for (string& s : arr)
		{
			int a = 0;
			for (char c : s)
				a |= 1 << (c - 'a');
			int n = popcnt(a);
			if (n < static_cast<int>(s.size()))
				continue;
			for (int i = static_cast<int>(dp.size() - 1);
				i >= 0; --i)
			{
				int c = dp[i];
				if (c & a)
					continue;
				dp.push_back(c | a);
				ans = max(ans, popcnt(c) + n);
			}
		}
		return ans;
	}
};


int main()
{
	vector<string>
		a = { "un", "iq", "ue" },
		b = { "cha", "r", "act", "ers" },
		c = { "abcdefghijklmnopqrstuvwxyz" };
	Solution s;
	OutExpr(s.maxLength(a), "%d");
	OutExpr(s.maxLength(b), "%d");
	OutExpr(s.maxLength(c), "%d");
}
