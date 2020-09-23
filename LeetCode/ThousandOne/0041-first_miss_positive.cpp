#include "leetcode.hpp"

/* 41. 缺失的第一个正数

给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。

示例 1:
输入: [1,2,0]
输出: 3

示例 2:
输入: [3,4,-1,1]
输出: 2

示例 3:
输入: [7,8,9,11,12]
输出: 1

提示：
你的算法的时间复杂度应为 O(n)，并且只能使用常数级别的额外空间。
*/

int firstMissingPositive(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int i = 0, k;
	for (; i < len;)
	{
		k = A[i] - 1U;
		if ((k != i)
			&& (static_cast<unsigned>(k) < static_cast<unsigned>(len))
			&& (A[k] != k + 1))
			std::swap(A[i], A[k]);
		else
			++i;
	}
	for (i = 1; i <= len; ++i)
	{
		if (A[i - 1] != i)
			break;
	}
	return i;
}

int main()
{
	vector<int>
		a = { 1, 2, 0 },
		b = { 3, 4, -1, 1 },
		c = { 7, 8, 9, 11, 12 };
	OutExpr(firstMissingPositive(a), "%d");
	OutExpr(firstMissingPositive(b), "%d");
	OutExpr(firstMissingPositive(c), "%d");
}
