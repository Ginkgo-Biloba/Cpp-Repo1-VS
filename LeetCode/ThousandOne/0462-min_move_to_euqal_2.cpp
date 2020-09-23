#include "leetcode.hpp"

/* 462. 最少移动次数使数组元素相等 II
给定一个非空整数数组，找到使所有数组元素相等所需的最小移动数，其中每次移动可将选定的一个元素加1或减1。 您可以假设数组的长度最多为10000。

例如:
输入:
[1,2,3]
输出:
2
说明：
只有两个动作是必要的（记得每一步仅可使其中一个元素加1或减1）：
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
*/

// 中位数？
int minMoves2(vector<int>& nums)
{
	size_t len = nums.size();
	if (len < 2)
		return 0;
	std::sort(nums.begin(), nums.end());
	int ans = 0;
	int mid = static_cast<int>(
		(INT64_C(1) + nums[len / 2] + nums[(len - 1) / 2])
		/ 2);
	for (size_t i = 0; i < len; ++i)
		ans += std::abs(nums[i] - mid);
	return ans;
}


int main()
{
	vector<int> nums = { 1, 2, 3 };
	OutExpr(minMoves2(nums), "%d");
}
