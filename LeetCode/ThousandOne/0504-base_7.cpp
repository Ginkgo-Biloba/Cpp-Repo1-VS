#include "leetcode.hpp"

/* 504. 七进制数

给定一个整数，将其转化为7进制，并以字符串形式输出。

示例 1:
输入: 100
输出: "202"

示例 2:
输入: -7
输出: "-10"

注意: 输入范围是 [-1e7, 1e7] 。
*/

string convertToBase7(int num)
{
	string b7;
	bool neg = num < 0;
	if (neg)
		num = -num;
	do
	{
		b7.push_back(static_cast<char>(num % 7 + '0'));
		num /= 7;
	} while (num > 0);
	if (neg)
		b7.push_back('-');
	std::reverse(b7.begin(), b7.end());
	return b7;
}


int main()
{
	OutExpr(convertToBase7(100).c_str(), "%s");
}
