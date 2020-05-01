#include "leetcode.hpp"

/* 1362. 最接近的因数

给你一个整数 num，请你找出同时满足下面全部要求的两个整数：
	两数乘积等于  num + 1 或 num + 2
	以绝对差进行度量，两数大小最接近

你可以按任意顺序返回这两个整数。

示例 1：
输入：num = 8
输出：[3,3]
解释：
对于 num + 1 = 9，最接近的两个因数是 3 & 3；
对于 num + 2 = 10, 最接近的两个因数是 2 & 5，因此返回 3 & 3 。

示例 2：
输入：num = 123
输出：[5,25]

示例 3：
输入：num = 999
输出：[40,25]

提示：
	1 <= num <= 10^9
*/

// https://leetcode.com/problems/closest-divisors/discuss/517595/JavaC%2B%2BPython-Easy-and-Concise
// 抄的
vector<int> closestDivisors(int num)
{
	vector<int> A(2);
	int n1 = num + 1, n2 = num + 2;
	A[0] = static_cast<int>(sqrt(n2) + 0.5);
	for (; A[0] > 0; --(A[0]))
	{
		A[1] = n1 / A[0];
		if (A[0] * A[1] == n1)
			break;
		A[1] = n2 / A[0];
		if (A[0] * A[1] == n2)
			break;
	}
	return A;
}


int main()
{
	output(closestDivisors(8));
	output(closestDivisors(123));
	output(closestDivisors(999));
}
