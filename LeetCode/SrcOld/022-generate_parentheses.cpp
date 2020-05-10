#include "leetcode.hpp"

/* 22. 括号生成

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例：
输入：n = 3
输出：
[
	"((()))",
	"(()())",
	"(())()",
	"()(())",
	"()()()"
]
*/

class Solution
{
	vector<string> ans;
	string cur;
	int total;

	void dfs(int left, int right)
	{
		if (left == right && left == total)
		{
			ans.push_back(cur);
			return;
		}
		cur.push_back('(');
		if (left < total)
			dfs(left + 1, right);
		cur.back() = ')';
		if (right < left)
			dfs(left, right + 1);
		cur.pop_back();
	}

public:
	vector<string> generateParenthesis(int n)
	{
		vector<string> t;
		total = n;
		cur.clear();
		dfs(0, 0);
		t.swap(ans);
		return t;
	}
};


int main()
{
	Solution s;
	output(s.generateParenthesis(3));
}
