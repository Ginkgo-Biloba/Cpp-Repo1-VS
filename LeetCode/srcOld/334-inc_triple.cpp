#include "../srcOld/utility.hpp"

/* 334. 递增的三元子序列

给定一个未排序的数组，判断这个数组中是否存在长度为 3 的递增子序列。
数学表达式如下:

如果存在这样的 i, j, k,  且满足 0 ≤ i < j < k ≤ n-1，
使得 arr[i] < arr[j] < arr[k] ，返回 true ; 否则返回 false 。

说明: 要求算法的时间复杂度为 O(n)，空间复杂度为 O(1) 。

示例 1:
输入: [1,2,3,4,5]
输出: true

示例 2:
输入: [5,4,3,2,1]
输出: false
*/

// https://leetcode.com/problems/increasing-triplet-subsequence/discuss/78993/Clean-and-short-with-comments-C%2B%2B
// asdfgc October 22, 2018 5:37 PM
// 抄的
bool increasingTriplet(vector<int>& nums)
{
	int x1 = INT_MAX, x2 = INT_MAX, x1alt = INT_MAX;
	size_t len = nums.size();

	for (size_t i = 0; i < len; ++i)
	{
		int y = nums[i];
		if (y <= x1)
		{
			if (y > x1alt)
			{
				x1 = x1alt;
				x2 = y;
				x1alt = INT_MAX;
			}
			else
				x1alt = y;
		}
		else if (y <= x2)
			x2 = y;
		else
		{
			// x1, x2, y
			return true;
		}
	}

	return false;
}

int main()
{
	vector<int> nums = { 1, 2, 2, 1 };
	bool n = increasingTriplet(nums);
	printf("increasingTriplet: %s\n", boolstr[n]);
}
