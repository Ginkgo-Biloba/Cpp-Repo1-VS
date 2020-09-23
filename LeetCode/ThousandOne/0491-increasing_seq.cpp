#include "leetcode.hpp"

/* 491. 递增子序列

给定一个整型数组, 你的任务是找到所有该数组的递增子序列，递增子序列的长度至少是2。

示例:

输入: [4, 6, 7, 7]
输出: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]

说明:

		给定数组的长度不会超过15。
		数组中的整数范围是 [-100,100]。
		给定数组中可能包含重复数字，相等的数字应该被视为递增的一种情况。
*/

// https://leetcode.com/problems/increasing-subsequences/discuss/97134/Evolve-from-intuitive-solution-to-optimal
// 抄的
vector<vector<int>> findSubsequences(vector<int> const& nums)
{
	vector<vector<int>> ans(1);
	unordered_map<int, int> ht;
	int len = static_cast<int>(nums.size());
	for (int i = 0; i < len; ++i)
	{
		int n = static_cast<int>(ans.size());
		int start = ht[nums[i]];
		ht[nums[i]] = n;
		for (int k = start; k < n; ++k)
			if (ans[k].empty() || ans[k].back() <= nums[i])
			{
				ans.push_back(ans[k]);
				ans.back().push_back(nums[i]);
			}
	}
	for (int i = static_cast<int>(ans.size()) - 1; i >= 0; --i)
		if (ans[i].size() < 2)
		{
			swap(ans[i], ans.back());
			ans.pop_back();
		}
	return ans;
}


int main()
{
	vector<int> nums = { 4, 6, 7, 7 };
	output(findSubsequences(nums), "findSubsequences");
}
