#include "leetcode.hpp"

/* 941. 有效的山脉数组

给定一个整数数组 A，如果它是有效的山脉数组就返回 true，否则返回 false。

让我们回顾一下，如果 A 满足下述条件，那么它是一个山脉数组：
	A.length >= 3
	在 0 < i < A.length - 1 条件下，存在 i 使得：
		A[0] < A[1] < ... A[i-1] < A[i]
		A[i] > A[i+1] > ... > A[B.length - 1]
https://assets.leetcode.com/uploads/2019/10/20/hint_valid_mountain_array.png

示例 1：
输入：[2,1]
输出：false

示例 2：
输入：[3,5,5]
输出：false

示例 3：
输入：[0,3,2,1]
输出：true

提示：
	0 <= A.length <= 10000
	0 <= A[i] <= 10000
*/

bool validMountainArray(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int i = 1;
	while (i < len && A[i - 1] < A[i])
		++i;
	if (i == 1 || i == len)
		return false;
	while (i < len && A[i - 1] > A[i])
		++i;
	return i == len;
}


int main()
{
	vector<int>
		a = { 2, 1 },
		b = { 3, 5, 5 },
		c = { 0, 3, 2, 1 };
	OutBool(validMountainArray(a));
	OutBool(validMountainArray(b));
	OutBool(validMountainArray(c));
}
