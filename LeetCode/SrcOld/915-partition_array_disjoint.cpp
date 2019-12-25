#include "leetcode.hpp"

/* 915. 分割数组

给定一个数组 A，将其划分为两个不相交（没有公共元素）的连续子数组 left 和 right，使得：
	left 中的每个元素都小于或等于 right 中的每个元素。
	left 和 right 都是非空的。
	left 要尽可能小。

在完成这样的分组后返回 left 的长度。可以保证存在这样的划分方法。

示例 1：
输入：[5,0,3,8,6]
输出：3
解释：left = [5,0,3]，right = [8,6]

示例 2：
输入：[1,1,1,0,6,12]
输出：4
解释：left = [1,1,1,0]，right = [6,12]

提示：
	2 <= A.length <= 30000
	0 <= A[i] <= 10^6
	可以保证至少有一种方法能够按题目所描述的那样对 A 进行划分。
*/

int partitionDisjoint(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<int> L = A, R = A;

	for (int i = 1; i < len; ++i)
		L[i] = max(L[i - 1], L[i]);
	for (int i = len - 2; i >= 0; --i)
		R[i] = min(R[i], R[i + 1]);

	for (int i = 1; i < len; ++i)
	{
		if (L[i - 1] <= R[i])
			return i;
	}
	return -1;
}

int main()
{
	vector<int>
		a = { 5, 0, 3, 8, 6 },
		b = { 1, 1, 1, 0, 6, 12 };
	OutExpr(partitionDisjoint(a), "%d");
	OutExpr(partitionDisjoint(b), "%d");
}
