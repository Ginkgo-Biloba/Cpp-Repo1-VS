#include "leetcode.hpp"

/* 154. 寻找旋转排序数组中的最小值 II

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

请找出其中最小的元素。

注意数组中可能存在重复的元素。

示例 1：
输入: [1,3,5]
输出: 1

示例 2：
输入: [2,2,2,0,1]
输出: 0

说明：
	这道题是 寻找旋转排序数组中的最小值 的延伸题目。
	允许重复会影响算法的时间复杂度吗？会如何影响，为什么？
*/

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/discuss/48808/My-pretty-simple-code-to-solve-it/48840
// 抄的
int findMin(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int a = 0, b, c = len - 1;
	while (a < c)
	{
		b = (a + c) / 2;
		if (A[b] > A[c])
			a = b + 1;
		else if (A[b] < A[c])
			c = b;
		else
		{
			if (A[c - 1] > A[c])
				a = c;
			else
				--c;
		}
	}
	return A[a];
}

int main()
{
	vector<int>
		a = { 3, 4, 5, 1, 2 },
		b = { 4, 5, 6, 7, 0, 1, 2 },
		c = { 2, 2, 2, 0, 1 };
	OutExpr(findMin(a), "%d");
	OutExpr(findMin(b), "%d");
	OutExpr(findMin(c), "%d");
}
