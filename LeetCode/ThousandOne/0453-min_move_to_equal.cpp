#include "leetcode.hpp"

/* 453. 最小移动次数使数组元素相等

给定一个长度为 n 的非空整数数组，找到让数组所有元素相等的最小移动次数。每次移动可以使 n - 1 个元素增加 1。

示例:
输入:
[1,2,3]
输出:
3

解释:
只需要3次移动（注意每次移动会增加两个元素的值）：
*/

int minMoves(vector<int>& nums)
{
	size_t len = nums.size();
	if (len < 2)
		return 0;
	int ans = 0;
	int val = nums[0];
	for (size_t i = 1; i < len; ++i)
		val = std::min(val, nums[i]);
	for (size_t i = 0; i < len; ++i)
		ans += (nums[i] - val);
	return ans;
}


int main()
{
	vector<int> nums = { 1, 2, 3 };
	OutExpr(minMoves(nums), "%d");
}
