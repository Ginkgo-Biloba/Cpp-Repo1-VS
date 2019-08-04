#include "leetcode.hpp"

/* 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
 * 返回 s 所有可能的分割方案。 */

 // https://leetcode.com/problems/palindrome-partitioning/discuss/41963/Java%3A-Backtracking-solution.
 // 抄的
class Solution
{
	vector<string> cur;
	vector<vector<string>> ans;

	bool isPalindrome(string const& s, size_t l, size_t r)
	{
		for (; l < r; ++l, --r)
		{
			if (s[l] != s[r])
				return false;
		}
		return true;
	}

	void backtrack(string const& s, size_t left)
	{
		if (cur.size() > 0 && left >= s.length()) // 整个字符串都可以回文
			ans.push_back(cur);
		for (size_t i = left; i < s.length(); ++i)
		{
			if (isPalindrome(s, left, i))
			{
				cur.push_back(s.substr(left, i + 1 - left));
				backtrack(s, i + 1);
				cur.pop_back();
			}
		}
	}
public:
	vector<vector<string>> partition(string const& str)
	{
		ans.clear(); cur.clear();
		backtrack(str, 0);
		return std::move(ans);
	}
};


int main()
{
	string str = "abbab";
	vector<vector<string>> ans = Solution().partition(str);
	for (size_t h = 0; h < ans.size(); ++h)
	{
		string const* ptr = ans[h].data();
		for (size_t w = 0; w < ans[h].size(); ++w)
			printf("%s, ", ptr[w].c_str());
		printf("\n");
	}
}
