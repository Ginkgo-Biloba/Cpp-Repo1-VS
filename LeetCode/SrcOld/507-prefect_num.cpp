#include "leetcode.hpp"

/* 507. 完美数

对于一个 正整数，如果它和除了它自身以外的所有正因子之和相等，我们称它为“完美数”。

给定一个 整数 n， 如果他是完美数，返回 True，否则返回 False

示例：
输入: 28
输出: True
解释: 28 = 1 + 2 + 4 + 7 + 14
*/

bool checkPerfectNumber(int num)
{
	int up = static_cast<int>(std::sqrt(num)) + 1;
	int sum = 1;
	for (int i = 2; i < up; ++i)
	{
		int k = num / i;
		if (k * i == num)
			sum += (k + i);
	}
	return sum == num;
}


int main()
{
	OutExpr(
		boolstr[checkPerfectNumber(6)],
		"%s");
}
