#include "leetcode.hpp"

/* 301. 删除无效的括号

删除最小数量的无效括号，使得输入的字符串有效，返回所有可能的结果。

说明: 输入可能包含了除 ( 和 ) 以外的字符。

示例 1:
输入: "()())()"
输出: ["()()()", "(())()"]

示例 2:
输入: "(a)())()"
输出: ["(a)()()", "(a())()"]

示例 3:
输入: ")("
输出: [""]
*/

// https://leetcode.com/problems/remove-invalid-parentheses/discuss/75027/Easy-Short-Concise-and-Fast-Java-DFS-3-ms-solution
// 抄的
class Solution1
{
	vector<string> ans;

	void rem(string s, int preI, int preK, char a, char b)
	{
		int len = static_cast<int>(s.size());
		int count = 0, i = preI, k;
		for (; i < len; ++i)
		{
			if (s[i] == a) ++count;
			if (s[i] == b) --count;
			if (count >= 0) continue;
			for (k = preK; k <= i; ++k)
			{
				if ((s[k] == b) && (k == preK || s[k - 1] != b))
					rem(s.substr(0, k) + s.substr(k + 1), i, k, a, b);
			}
			return;
		}
		reverse(s.begin(), s.end());
		if (a == '(')
			rem(s, 0, 0, ')', '(');
		else
			ans.push_back(s);
	}

public:
	vector<string> removeInvalidParentheses(string s)
	{
		rem(s, 0, 0, '(', ')');
		vector<string> R;
		R.swap(ans);
		return R;
	}
};


// https://leetcode.com/problems/remove-invalid-parentheses/discuss/75038/Evolve-from-intuitive-solution-to-optimal-a-review-of-all-solutions
// 抄的
class Solution
{
public:
	// 抄的
	struct Status
	{
		string str;
		int start, lastRm;
		char rmCh;
	};

	vector<string> removeInvalidParentheses(string s)
	{
		vector<string> ans;
		std::queue<Status> q;
		q.push({ s, 0, 0, '(' });

		while (!q.empty())
		{
			Status st = q.front();
			q.pop();
			string& str = st.str;
			int count = 0, len = static_cast<int>(str.size());
			char l = st.rmCh, r = (l == '(') ? ')' : '(';

			for (int i = st.start; i < len; ++i)
			{
				if (str[i] == l) ++count;
				else if (str[i] == r) --count;
				if (count >= 0) continue;

				for (int k = st.lastRm; k <= i; ++k)
				{
					if (str[k] == r && (k == st.lastRm || str[k - 1] != r))
						q.push({ str.substr(0, k) + str.substr(k + 1), i, k, l });
				}
				break;
			}

			if (count < 0) 
				continue;

			reverse(str.begin(), str.end());
			if (l == '(')
				q.push({ str, 0, 0, ')' });
			else
				ans.push_back(str);
		}

		return ans;
	}
};

int main()
{
	Solution s;
	output(s.removeInvalidParentheses("()())()"), ", ");
	output(s.removeInvalidParentheses("(a)())()"), ", ");
	output(s.removeInvalidParentheses(")("), ", ");
}
