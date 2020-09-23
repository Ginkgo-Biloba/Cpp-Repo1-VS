#include "leetcode.hpp"

/* 32. 最长有效括号

给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。

示例 1:
输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"

示例 2:
输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"
*/

int longestValidParentheses(string s)
{
	int len = static_cast<int>(s.size());
	int ans = 0, cur, pre = -1;
	vector<int> idx;
	idx.reserve(len);
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == '(')
			idx.push_back(i);
		else
		{
			// ())|() 这个 ) 不构成合法序列，下次从下一个字符算起
			if (idx.empty())
				pre = i;
			else
			{
				idx.pop_back();
				// ()|()
				if (idx.empty())
					cur = i - pre;
				// (|()
				else
					cur = i - idx.back();
				ans = max(cur, ans);
			}
		}
	}
	return ans;
}

int main()
{
	OutExpr(longestValidParentheses("(()"), "%d");
	OutExpr(longestValidParentheses(")()())"), "%d");
	OutExpr(longestValidParentheses("())())"), "%d");
}
