#include "leetcode.hpp"

/* 35. 搜索插入位置

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。

示例 1:
输入: [1,3,5,6], 5
输出: 2

示例 2:
输入: [1,3,5,6], 2
输出: 1

示例 3:
输入: [1,3,5,6], 7
输出: 4

示例 4:
输入: [1,3,5,6], 0
输出: 0
*/

// std::lower_bound
int searchInsert(vector<int>& A, int val)
{
	int len = static_cast<int>(A.size());
	int h = 0, i, k = len;
	while (h < k)
	{
		i = (h + k) / 2;
		if (A[i] < val)
			h = i + 1;
		else
			k = i;
	}
	return h;
}

int main()
{
	vector<int> a = { 1, 3, 5, 6 };
	OutExpr(searchInsert(a, 5), "%d");
	OutExpr(searchInsert(a, 2), "%d");
	OutExpr(searchInsert(a, 7), "%d");
	OutExpr(searchInsert(a, 0), "%d");
}
