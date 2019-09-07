#include "leetcode.hpp"

/* 485. 最大连续 1 的个数

给定一个二进制数组， 计算其中最大连续1的个数。

示例 1:
输入: [1,1,0,1,1,1]
输出: 3
解释: 开头的两位和最后的三位都是连续 1，所以最大连续 1 的个数是 3.

注意：
		输入的数组只包含 0 和1。
		输入数组的长度是正整数，且不超过 10,000。
*/

int findMaxConsecutiveOnes(vector<int> const& nums)
{
	size_t len = nums.size();
	int maxlen = 0, curlen = 0;
	for (size_t i = 0; i < len; ++i)
	{
		if (nums[i] == 1)
		{
			++curlen;
			maxlen = std::max(maxlen, curlen);
		}
		else
			curlen = 0;
	}
	return maxlen;
}


int main()
{
	vector<int> nums = { 1, 1, 0, 1, 1, 1 };
	OutExpr(findMaxConsecutiveOnes(nums), "%d");
}
