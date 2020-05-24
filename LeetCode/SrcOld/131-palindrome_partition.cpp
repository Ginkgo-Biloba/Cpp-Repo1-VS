#include "leetcode.hpp"

/* 131. 分割回文串

给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

返回 s 所有可能的分割方案。

示例:
输入: "aab"
输出:
[
	["aa","b"],
	["a","a","b"]
]
*/

// https://leetcode.com/problems/palindrome-partitioning/discuss/41964/Clean-C%2B%2B-backtracking-solution
// 抄的
class Solution
{
	vector<string> cur;
	vector<vector<string>> ans;
	string str;

	bool isPalindrome(size_t l, size_t r)
	{
		for (; l < r; ++l, --r)
		{
			if (str[l] != str[r])
				return false;
		}
		return true;
	}

	void backtrack(size_t left)
	{
		// 整个字符串都可以回文
		if (cur.size() > 0 && left >= str.length())
			ans.push_back(cur);
		for (size_t i = left; i < str.length(); ++i)
		{
			if (isPalindrome(left, i))
			{
				cur.push_back(str.substr(left, i + 1 - left));
				backtrack(i + 1);
				cur.pop_back();
			}
		}
	}

public:
	vector<vector<string>> partition(string s)
	{
		str.swap(s);
		cur.clear();
		backtrack(0);
		vector<vector<string>> R;
		R.swap(ans);
		return R;
	}
};


int main()
{
	Solution sln;
	vector<vector<string>> r = sln.partition("aab");
	for (auto& vs : r)
	{
		for (string& s : vs)
			printf("%s, ", s.c_str());
		puts("");
	}
}
