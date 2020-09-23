#include "leetcode.hpp"

/* 670. 最大交换

给定一个非负整数，你至多可以交换一次数字中的任意两位。返回你能得到的最大值。

示例 1 :
输入: 2736
输出: 7236
解释: 交换数字2和数字7。

示例 2 :
输入: 9973
输出: 9973
解释: 不需要交换。

注意:
	给定数字的范围是 [0, 108]
*/


int maximumSwap(int num)
{
	int last[10], bits[10];
	int left = 10, right = 10;
	int n = num;
	memset(last, 0xff, sizeof(last));
	while (n)
	{
		int b = n % 10;
		--left;
		bits[left] = b;
		if (last[b] == -1)
			last[b] = left;
		n /= 10;
	}
	for (int i = left; i < right; ++i)
		for (int b = 9; b > bits[i]; --b)
			if (last[b] > i)
			{
				std::swap(bits[i], bits[last[b]]);
				i = right;
				break;
			}
	n = 0;
	for (int i = left; i < right; ++i)
	{
		n *= 10;
		n += bits[i];
	}
	return n;
}


int main()
{
	OutExpr(maximumSwap(2736), "%d");
	OutExpr(maximumSwap(9973), "%d");
	OutExpr(maximumSwap(9879), "%d");
	OutExpr(maximumSwap(99167), "%d");
	OutExpr(maximumSwap(0), "%d");
	OutExpr(maximumSwap(10), "%d");
	OutExpr(maximumSwap(999), "%d");
}
