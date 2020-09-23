#include "leetcode.hpp"

/* 287. 寻找重复数

给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
假设只有一个重复的整数，找出这个重复的数。

示例 1:

输入: [1,3,4,2,2]
输出: 2

示例 2:

输入: [3,1,3,4,2]
输出: 3

说明：
	不能更改原数组（假设数组是只读的）。
	只能使用额外的 O(1) 的空间。
	时间复杂度小于 O(n^2) 。
	数组中只有一个重复的数字，但它可能不止重复出现一次。
*/

int findDuplicate(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	for (int i = 0; i < len;)
	{
		if (A[i] == i + 1)
			++i;
		else
		{
			if (A[A[i] - 1] != A[i])
				std::swap(A[A[i] - 1], A[i]);
			else
				return A[i];
		}
	}
	return 0;
}


int main()
{
	vector<int>
		a = { 1, 3, 4, 2, 2 },
		b = { 3, 1, 3, 4, 2 },
		c = { 1, 1, 2 },
		d = { 3, 3, 3, 3 };
	OutExpr(findDuplicate(a), "%d");
	OutExpr(findDuplicate(b), "%d");
	OutExpr(findDuplicate(c), "%d");
	OutExpr(findDuplicate(d), "%d");
}
