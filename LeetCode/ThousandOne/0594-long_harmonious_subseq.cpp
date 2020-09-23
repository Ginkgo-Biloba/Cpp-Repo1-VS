#include "leetcode.hpp"

/* 594. 最长和谐子序列

和谐数组是指一个数组里元素的最大值和最小值之间的差别正好是1。

现在，给定一个整数数组，你需要在所有可能的子序列中找到最长的和谐子序列的长度。

示例 1:
输入: [1,3,2,2,5,2,3,7]
输出: 5
原因: 最长的和谐数组是：[3,2,2,2,3].

说明: 输入的数组长度最大不超过20,000.
*/

int findLHS(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	if (len < 1)
		return 0;

	sort(nums.begin(), nums.end());
	int maxlen = 0;
	int nprev = 0, ncur = 0;
	int prev = nums[0], cur = nums[0];
	for (int i = 0; i < len;)
	{
		cur = nums[i];
		ncur = 0;
		while (i < len && nums[i] == cur)
		{
			++i;
			++ncur;
		}
		if (prev + 1 == cur)
			maxlen = std::max(maxlen, nprev + ncur);
		nprev = ncur;
		prev = cur;
	}
	return maxlen;
}


int main()
{
	vector<int> nums = { 1, 3, 2, 2, 5, 2, 3, 7 };
	OutExpr(findLHS(nums), "%d");
}
