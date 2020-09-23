#include "leetcode.hpp"

/* 153. 寻找旋转排序数组中的最小值

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

请找出其中最小的元素。

你可以假设数组中不存在重复元素。

示例 1:
输入: [3,4,5,1,2]
输出: 1

示例 2:
输入: [4,5,6,7,0,1,2]
输出: 0
*/

int findMin(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int a = 0, b, c = len - 1;
	while (a < c)
	{
		if (A[a] < A[c])
			break;

		b = (a + c) / 2;
		if (A[a] <= A[b])
			a = b + 1;
		else
			c = b;
	}
	return A[a];
}


int main()
{
	vector<int>
		a = { 3, 4, 5, 1, 2 },
		b = { 4, 5, 6, 7, 0, 1, 2 },
		c = { 2, 1 };
	OutExpr(findMin(a), "%d");
	OutExpr(findMin(b), "%d");
	OutExpr(findMin(c), "%d");
}
