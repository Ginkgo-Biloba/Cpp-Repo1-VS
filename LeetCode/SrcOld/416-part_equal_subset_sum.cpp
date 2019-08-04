#include "leetcode.hpp"

/* 416. 分割等和子集

给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
注意:
		每个数组中的元素不会超过 100
		数组的大小不会超过 200

示例 1:
输入: [1, 5, 11, 5]
输出: true
解释: 数组可以分割成 [1, 5, 5] 和 [11].

示例 2:
输入: [1, 2, 3, 5]
输出: false
解释: 数组不能分割成两个元素和相等的子集.
*/


bool canPartition(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	int sum = 0;
	for (int i = 0; i < len; ++i)
		sum += nums[i];
	if (sum & 1)
		return false;
	sum = sum / 2;

	vector<char> dp(sum + 1, '\0');
	dp[0] = 1;

	for (int i = 0; i < len; ++i)
	{
		int cur = nums[i];
		for (int k = sum; k >= cur; --k)
			dp[k] |= dp[k - cur];
	}

	return dp[sum] == 1;
}


int main()
{
	vector<int> nums = { 1, 5, 11, 5 };
	OutExpr(boolstr[canPartition(nums)], "%s");
}

