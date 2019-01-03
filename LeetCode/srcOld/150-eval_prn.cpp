#include "../src/utility.hpp"


int evalRPN(vector<string> const& tokens)
{
	vector<int> nums; nums.reserve(tokens.size());

	for (string const& token : tokens)
	{
		char const val = token[0];
		// 注意负数开头是 -
		if (token.size() == (size_t)(1) && \
			((val == '+') || (val == '-') || (val == '*') || (val == '/')))
		{
			int y = nums.back(); nums.pop_back();
			int x = nums.back(); nums.pop_back();
			if (val == '+') x += y;
			else if (val == '-') x -= y;
			else if (val == '*') x *= y;
			else/* if (val == '*')*/ x /= y;
			nums.push_back(x);
		}
		else
			nums.push_back(atoi(token.c_str()));
	}

	return nums[0]; // nums.size() == 1
}



int main()
{
	vector<string> str
		= { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
	int ans = evalRPN(str);
	printf("%1s = %d\n", "evalRPN", ans);
}
