#include "leetcode.hpp"

/* 560. 和为K的子数组

给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

示例 1 :

输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。

说明 :
		数组的长度为 [1, 20,000]。
		数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。
*/


// 抄的答案
int subarraySum(vector<int>& nums, int k)
{
	size_t len = nums.size();
	int count = 0, sum = 0;
	unordered_map<int, int> um;
	um[0] = 1;
	for (size_t i = 0; i < len; ++i)
	{
		sum += nums[i];
		if (um.find(sum - k) != um.end())
			count += um[sum - k];
		um[sum] += 1;
	}
	return count;
}


int main()
{
	vector<int> nums = { 1, 1, 1 };
	OutExpr(subarraySum(nums, 2), "%d");
}
