#include "../srcOld/utility.hpp"
#include <amp.h>

/* 402. 移掉K位数字

给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

注意:
num 的长度小于 10002 且 ≥ k。
num 不会包含任何前导零。

示例 1 
输入: num = "1432219", k = 3
输出: "1219"
解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。

示例 2 :
输入: num = "10200", k = 1
输出: "200"
解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。

示例 3 :
输入: num = "10", k = 2
输出: "0"
解释: 从原数字移除所有的数字，剩余为空就是0。
*/

string removeKdigits(string const& num, int k)
{
	int len = static_cast<int>(num.size());
	string inc("0");
	if (k >= len)
		return inc;
	inc.pop_back();

	for (int i = 0; i < len; ++i)
	{
		for (; !inc.empty() && k > 0 && (num[i] < inc.back()); --k)
			inc.pop_back();
		inc.push_back(num[i]);
	}

	for (; k > 0; --k)
		inc.pop_back();

	reverse(inc.begin(), inc.end());
	while (!inc.empty() && inc.back() == '0')
		inc.pop_back();
	reverse(inc.begin(), inc.end());
	if (inc.empty())
		inc.push_back('0');

	return inc;
}


int main()
{
	OutExpr(removeKdigits("10200", 1).c_str(), "%s");
};

