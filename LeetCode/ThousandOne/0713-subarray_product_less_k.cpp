#include "leetcode.hpp"

/* 713. 乘积小于K的子数组

给定一个正整数数组 nums。

找出该数组内乘积小于 k 的连续的子数组的个数。

示例 1:
输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8个乘积小于100的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于100的子数组。

说明:
	0 < nums.length <= 50000
	0 < nums[i] < 1000
	0 <= k < 10^6
*/

int numSubarrayProductLessThanK(vector<int>& nums, int k)
{
	int len = static_cast<int>(nums.size());
	int L = 0, R = 1, pdt = 1, ans = 0;
	for (; R <= len; ++R)
	{
		pdt *= nums[R - 1];
		for (; L < R && pdt >= k; ++L)
			pdt /= nums[L];
		ans += R - L;
	}
	return ans;
}


int main()
{
	vector<int> nums1 = { 10, 5, 2, 6 };
	vector<int> nums2 = { 10, 9, 10, 4, 3, 8, 3, 3, 6, 2, 10, 10, 9, 3 };
	OutExpr(numSubarrayProductLessThanK(nums1, 100), "%d");
	OutExpr(numSubarrayProductLessThanK(nums2, 19), "%d");
}
