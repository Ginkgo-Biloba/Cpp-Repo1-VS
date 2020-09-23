#include "leetcode.hpp"

/* 189. 旋转数组

给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

示例 1:
输入: [1,2,3,4,5,6,7] 和 k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]

示例 2:
输入: [-1,-100,3,99] 和 k = 2
输出: [3,99,-1,-100]
解释:
向右旋转 1 步: [99,-1,-100,3]
向右旋转 2 步: [3,99,-1,-100]

说明:
	尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
	要求使用空间复杂度为 O(1) 的 原地 算法。
*/

void reverse(vector<int>& A, int h, int i)
{
	for (--i; h < i; ++h, --i)
	{
		int t = A[h];
		A[h] = A[i];
		A[i] = t;
	}
}

void rotate(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	k = len - k % len;
	reverse(A, 0, k);
	reverse(A, k, len);
	reverse(A, 0, len);
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 4, 5, 6, 7 },
		b = { -1, -100, 3, 99 };
	rotate(a, 3);
	rotate(b, 2);
}
