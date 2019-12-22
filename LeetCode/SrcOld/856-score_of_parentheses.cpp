#include "leetcode.hpp"

/* 856. 括号的分数

给定一个平衡括号字符串 S，按下述规则计算该字符串的分数：
	() 得 1 分。
	AB 得 A + B 分，其中 A 和 B 是平衡括号字符串。
	(A) 得 2 * A 分，其中 A 是平衡括号字符串。

示例 1：
输入： "()"
输出： 1

示例 2：
输入： "(())"
输出： 2

示例 3：
输入： "()()"
输出： 2

示例 4：
输入： "(()(()))"
输出： 6

提示：
	S 是平衡括号字符串，且只含有 ( 和 ) 。
	2 <= S.length <= 50
*/

// https://leetcode.com/problems/score-of-parentheses/discuss/141777/C%2B%2BJavaPython-O(1)-Space
// 抄的
int scoreOfParentheses1(string S)
{
	vector<int> q;
	int cur = 0;
	q.reserve(S.size() / 2);
	for (char c : S)
	{
		if (c == '(')
		{
			q.push_back(cur);
			cur = 0;
		}
		else
		{
			cur = std::max(2 * cur, 1);
			cur += q.back();
			q.pop_back();
		}
	}
	return cur;
}

// https://leetcode-cn.com/problems/score-of-parentheses/solution/gua-hao-de-fen-shu-by-leetcode/
int scoreOfParentheses(string S)
{
	vector<int> q;
	q.reserve(S.size() / 2 + 1);
	q.push_back(0);
	for (char c : S)
	{
		if (c == '(')
			q.push_back(0);
		else
		{
			int cur = std::max(q.back() * 2, 1);
			q.pop_back();
			q.back() += cur;
		}
	}
	return q[0]; // q.size() == 1
}


int main()
{
	OutExpr(scoreOfParentheses("()"), "%d");
	OutExpr(scoreOfParentheses("(())"), "%d");
	OutExpr(scoreOfParentheses("()()"), "%d");
	OutExpr(scoreOfParentheses("(()(()))"), "%d");
}
