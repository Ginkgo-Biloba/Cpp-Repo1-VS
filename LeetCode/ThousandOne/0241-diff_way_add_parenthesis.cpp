#include "leetcode.hpp"

/* 241. 为运算表达式设计优先级

给定一个含有数字和运算符的字符串，为表达式添加括号，改变其运算优先级以求出不同的结果。
你需要给出所有可能的组合的结果。
有效的运算符号包含 +, - 以及 * 。

示例 1:
输入: "2-1-1"
输出: [0, 2]
解释:
((2-1)-1) = 0
(2-(1-1)) = 2

示例 2:
输入: "2*3-4*5"
输出: [-34, -14, -10, -10, 10]
解释:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
*/

// https://leetcode.com/problems/different-ways-to-add-parentheses/discuss/66351/C%2B%2B-solution-using-dp-easy-understanding
// 抄的
vector<int> diffWaysToCompute(string input)
{
	vector<int> data;
	string ops;
	std::istringstream iss(input + '+');
	int num;
	char ch;
	while (iss >> num && iss >> ch)
	{
		data.push_back(num);
		ops.push_back(ch);
	}
	int len = static_cast<int>(data.size());
	if (len == 0)
		return data;

	vector<vector<int>> dp(len * len);
	for (int k = 0; k < len; ++k)
		for (int h = k; h >= 0; --h)
		{
			vector<int>& R = dp[h * len + k];
			if (h == k)
			{
				// 从 h 到 k 的结果
				R.push_back(data[h]);
				continue;
			}
			for (int i = h; i < k; ++i)
			{
				vector<int>& A = dp[h * len + i];
				vector<int>& B = dp[(i + 1) * len + k];
				ch = ops[i];
				for (int a : A)
					for (int b : B)
					{
						if (ch == '+')
							num = a + b;
						else if (ch == '-')
							num = a - b;
						else
							num = a * b;
						R.push_back(num);
					}
			}
		}

	return dp[0 * len + (len - 1)];
}


int main()
{
	output(diffWaysToCompute("2-1-1"), "Different Ways");
	output(diffWaysToCompute("2*3-4*5"), "Different Ways");
	output(diffWaysToCompute(""), "Different Ways");
}
