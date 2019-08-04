#include "leetcode.hpp"

/* 删除最小数量的无效括号，使得输入的字符串有效，返回所有可能的结果 */

// https://leetcode.com/problems/remove-invalid-parentheses/discuss/75038/Evolve-from-intuitive-solution-to-optimal-a-review-of-all-solutions
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
					q.push({str.substr(0, k) + str.substr(k + 1), i, k, l});
			}
			break;
		}

		if (count < 0) continue;
		std::reverse(str.begin(), str.end());
		if (l == '(') q.push({ str, 0, 0, ')' });
		else ans.push_back(str);
	}

	return ans;
}


int main()
{
	string str = "(a)())()";
	vector<string> ans = removeInvalidParentheses(str);
	output(ans, "\n", "Remove Invalid Parentheses");
}
