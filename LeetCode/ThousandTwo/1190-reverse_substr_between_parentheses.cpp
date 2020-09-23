#include "leetcode.hpp"

/* 1190. 反转每对括号间的子串

给出一个字符串 s（仅含有小写英文字母和括号）。

请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。

注意，您的结果中 不应 包含任何括号。

示例 1：
输入：s = "(abcd)"
输出："dcba"

示例 2：
输入：s = "(u(love)i)"
输出："iloveu"

示例 3：
输入：s = "(ed(et(oc))el)"
输出："leetcode"

示例 4：
输入：s = "a(bcdefghijkl(mno)p)q"
输出："apmnolkjihgfedcbq"

提示：
	0 <= s.length <= 2000
	s 中只有小写英文字母和括号
	我们确保所有括号都是成对出现的
*/


string reverseParentheses1(string const& s)
{
	string ans;
	int len = static_cast<int>(s.size());
	ans.reserve(s.size());
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == '(')
		{
			int left = 1;
			int k = i + 1;
			for (; left > 0; ++k)
			{
				if (s[k] == '(')
					++left;
				else if (s[k] == ')')
					--left;
			}
			string t = s.substr(i + 1, k - i - 2);
			reverseParentheses1(t).swap(t);
			reverse(t.begin(), t.end());
			ans.append(t);
			i = k - 1;
		}
		else
			ans.push_back(s[i]);
	}
	return ans;
}

// https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/discuss/383670/JavaC%2B%2BPython-Why-not-O(N)
// 抄的
string reverseParentheses(string const& s)
{
	int n = static_cast<int>(s.size());
	vector<int> left, pare(n);
	string t;
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == '(')
			left.push_back(i);
		if (s[i] == ')')
		{
			int h = left.back();
			left.pop_back();
			pare[i] = h;
			pare[h] = i;
		}
	}
	t.reserve(n);
	for (int i = 0, d = 1; i < n; i += d)
	{
		if (s[i] == '(' || s[i] == ')')
		{
			i = pare[i];
			d = -d;
		}
		else
			t.push_back(s[i]);
	}
	return t;
}


int main()
{
	OutString(reverseParentheses("(abcd)"));
	OutString(reverseParentheses("(u(love)i)"));
	OutString(reverseParentheses("(ed(et(oc))el)"));
	OutString(reverseParentheses("a(bcdefghijkl(mno)p)q"));
}
