#include "leetcode.hpp"

/* 442. 数组中重复的数据

给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次。
找到所有出现两次的元素。
你可以不用到任何额外空间并在O(n)时间复杂度内解决这个问题吗？

示例：
输入:
[4,3,2,7,8,2,3,1]
输出:
[2,3]
*/

vector<int> findDuplicates(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	vector<int> ans;
	if (len == 0)
		return ans;

	// - 1 后方便
	for (int i = 0; i < len; ++i)
		--nums[i];
	for (int i = 0; i < len;)
	{
		if (nums[i] == i || nums[i] == nums[nums[i]])
			++i;
		else
			std::swap(nums[i], nums[nums[i]]);
	}
	for (int i = 0; i < len; ++i)
	{
		if (nums[i] != i)
			ans.push_back(nums[i] + 1);
	}

	return ans;
}


int main()
{
	vector<int> nums = { 4, 3, 2, 7, 8, 2, 3, 1 };
	output(findDuplicates(nums), "findDuplicates");
}
