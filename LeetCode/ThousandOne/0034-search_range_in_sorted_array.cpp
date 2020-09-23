#include "leetcode.hpp"

/* 34. 在排序数组中查找元素的第一个和最后一个位置

给定一个按照升序排列的整数数组 nums，和一个目标值 target。
找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。

示例 1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]

示例 2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
*/

vector<int> searchRange(vector<int>& A, int val)
{
	int len = static_cast<int>(A.size());
	vector<int> R(2, -1);
	if (len == 0)
		return R;
	int h = 0, i, k = len - 1;
	while (h < i)
	{
		i = (h + k) / 2;
		if (A[i] < val)
			h = i + 1;
		else
			k = i;
	}
	if (A[h] != val)
		return R;
	R[0] = h;
	k = len;
	while (h < k)
	{
		i = (h + k) / 2;
		if (A[i] <= val)
			h = i + 1;
		else
			k = i;
	}
	R[1] = h - 1;
	return R;
}

int main()
{
	vector<int> a = { 5, 7, 7, 8, 8, 10 };
	output(searchRange(a, 8), "searchRange");
	output(searchRange(a, 6), "searchRange");
}
