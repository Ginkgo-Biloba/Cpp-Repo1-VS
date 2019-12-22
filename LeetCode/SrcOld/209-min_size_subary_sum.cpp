#include "leetcode.hpp"

/* 209. 长度最小的子数组

给定一个含有 n 个正整数的数组和一个正整数 s，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。
如果不存在符合条件的连续子数组，返回 0。

示例:
输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。

进阶:
如果你已经完成了O(n) 时间复杂度的解法, 请尝试 O(n log n) 时间复杂度的解法。
*/

int minSubArrayLen(int target, vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	int ans = len + 1;
	int prev = 0;
	for (int i = 0; i < len; ++i)
	{
		target -= nums[i];
		while (target <= 0)
		{
			ans = std::min(ans, i - prev + 1);
			target += nums[prev];
			++prev;
		}
	}
	return (ans > len) ? 0 : ans;
}

int main()
{
	vector<int> a = { 2, 3, 1, 2, 4, 3 };
	OutExpr(minSubArrayLen(7, a), "%d");
}
