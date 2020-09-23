#include "leetcode.hpp"

/* 665. 非递减数列

给定一个长度为 n 的整数数组，你的任务是判断在最多改变 1 个元素的情况下，该数组能否变成一个非递减数列。
我们是这样定义一个非递减数列的：
对于数组中所有的 i (1 <= i < n)，满足 array[i] <= array[i + 1]。

示例 1:
输入: [4,2,3]
输出: True
解释: 你可以通过把第一个4变成1来使得它成为一个非递减数列。

示例 2:
输入: [4,2,1]
输出: False
解释: 你不能在只改变一个元素的情况下将其变为非递减数列。

说明:  n 的范围为 [1, 10,000]。
*/

// https://leetcode.com/problems/non-decreasing-array/discuss/106826/JavaC%2B%2B-Simple-greedy-like-solution-with-explanation
// 抄的
bool checkPossibility(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	bool ops = false;
	for (int i = 1; i < len; ++i)
		if (nums[i - 1] > nums[i])
		{
			if (ops)
				return false;
			ops = true;
			if (i - 2 < 0 || nums[i - 2] <= nums[i])
				nums[i - 1] = nums[i];
			else
				nums[i] = nums[i - 1];
		}
	return true;
}

int main()
{
	vector<int> nums = { 4, 2, 3 };
	OutExpr(boolstr[checkPossibility(nums)], "%s");
	nums = { 4, 2, 1 };
	OutExpr(boolstr[checkPossibility(nums)], "%s");
}
