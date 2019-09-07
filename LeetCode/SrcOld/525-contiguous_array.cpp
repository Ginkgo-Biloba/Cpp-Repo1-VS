#include "leetcode.hpp"

/* 525. 连续数组

给定一个二进制数组, 找到含有相同数量的 0 和 1 的最长连续子数组（的长度）。

示例 1:
输入: [0,1]
输出: 2
说明: [0, 1] 是具有相同数量0和1的最长连续子数组。

示例 2:
输入: [0,1,0]
输出: 2
说明: [0, 1] (或 [1, 0]) 是具有相同数量0和1的最长连续子数组。

注意: 给定的二进制数组的长度不会超过50000。。
*/

// https://leetcode.com/problems/contiguous-array/discuss/99655/Python-O(n)-Solution-with-Visual-Explanation
// 抄的
int findMaxLength(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	int count = 0;
	int maxlen = 0;
	unordered_map<int, int> um;
	um.emplace(0, -1);
	for (int i = 0; i < len; ++i)
	{
		// count += (nums[i] ? 1 : -1);
		count += (2 * nums[i] - 1);
		if (um.find(count) != um.end())
			maxlen = std::max(maxlen, i - um[count]);
		else
			um[count] = i;
	}
	return maxlen;
}


int main()
{
	vector<int> nums = { 0, 1, 0, 0, 1, 1 };
	OutExpr(findMaxLength(nums), "%d");
}
