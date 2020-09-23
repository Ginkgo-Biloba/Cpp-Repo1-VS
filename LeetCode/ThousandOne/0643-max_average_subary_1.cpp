#include "leetcode.hpp"

/* 643. 子数组最大平均数 I

给定 n 个整数，找出平均数最大且长度为 k 的连续子数组，并输出该最大平均数。

示例 1:
输入: [1,12,-5,-6,50,3], k = 4
输出: 12.75
解释: 最大平均数 (12-5-6+50)/4 = 51/4 = 12.75

注意:
	1 <= k <= n <= 30,000。
	所给数据范围 [-10,000，10,000]。
*/

// boxFilter
double findMaxAverage(vector<int>& nums, int k)
{
	int sum = 0, t = INT_MIN;
	int len = static_cast<int>(nums.size());
	int km1 = k - 1;
	for (int i = 0; i < km1; ++i)
		sum += nums[i];
	for (int i = km1; i < len; ++i)
	{
		sum += nums[i];
		t = std::max(t, sum);
		sum -= nums[i - km1];
	}
	return static_cast<double>(t) / k;
}


int main()
{
	vector<int> nums = { 1, 12, -5, -6, 50, 3 };
	OutExpr(findMaxAverage(nums, 4), "%f");
}
