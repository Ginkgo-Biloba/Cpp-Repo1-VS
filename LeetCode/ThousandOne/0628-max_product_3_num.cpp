#include "leetcode.hpp"

/* 628. 三个数的最大乘积

给定一个整型数组，在数组中找出由三个数组成的最大乘积，并输出这个乘积。

示例 1:
输入: [1,2,3]
输出: 6

示例 2:
输入: [1,2,3,4]
输出: 24

注意:
	给定的整型数组长度范围是[3,104]，数组中所有的元素范围是[-1000, 1000]。
	输入的数组中任意三个数的乘积不会超出32位有符号整数的范围。
*/

int maximumProduct(vector<int>& nums)
{
	sort(nums.begin(), nums.end());
	int len = static_cast<int>(nums.size());
	int v0 = nums[len - 1] * nums[len - 2] * nums[len - 3];
	int v1 = nums[len - 1] * nums[1] * nums[0];
	return std::max(v0, v1);
}


int main()
{
	vector<int> nums = { -1, 2, -3, 4 };
	OutExpr(maximumProduct(nums), "%d");
}
