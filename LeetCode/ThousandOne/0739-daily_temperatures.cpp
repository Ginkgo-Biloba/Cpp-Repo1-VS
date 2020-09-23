#include "leetcode.hpp"

/* 739. 每日温度

根据每日气温列表，请重新生成一个列表，对应位置的输入是你需要再等待多久温度才会升高超过该日的天数。如果之后都不会升高，请在该位置用 0 来代替。

例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，
你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

提示：
	气温列表长度的范围是 [1, 30000]。
	每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。
*/

vector<int> dailyTemperatures(vector<int>& T)
{
	int len = static_cast<int>(T.size());
	vector<int> ans(len), stk;
	stk.reserve(len);

	for (int i = 0; i < len; ++i)
	{
		while (!stk.empty() && T[stk.back()] < T[i])
		{
			ans[stk.back()] = i - stk.back();
			stk.pop_back();
		}
		stk.push_back(i);
	}

	return ans;
}


int main()
{
	vector<int> T1 = { 73, 74, 75, 71, 69, 72, 76, 73 };
	output(dailyTemperatures(T1), "Daily Temperatures");
}
