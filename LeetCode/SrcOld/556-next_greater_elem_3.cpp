#include "leetcode.hpp"

/* 556. 下一个更大元素 III

给定一个32位正整数 n，你需要找到最小的32位整数，其与 n 中存在的位数完全相同，并且其值大于n。如果不存在这样的32位整数，则返回-1。

示例 1:

输入: 12
输出: 21

示例 2:

输入: 21
输出: -1
*/


int nextGreaterElement(int n)
{
	int b[16], i = 15;
	int64_t N = n;
	for (; N > 0; --i)
	{
		b[i] = N % 10;
		N /= 10;
	}
	++i;
	std::next_permutation(b + i, b + 16);
	N = 0;
	for (; i < 16; ++i)
	{
		N *= 10;
		N += b[i];
	}
	if (N > n && N <= INT_MAX)
		n = static_cast<int>(N);
	else
		n = -1;
	return n;
}


int main()
{
	OutExpr(nextGreaterElement(1999999999), "%d");
}
