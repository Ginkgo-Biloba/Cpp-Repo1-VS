#include "../src/utility.hpp"

/** House Robber II
 * 第一个和最后一个房子挨着，是个环 */
int rob(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	switch (len)
	{
	case 0: return 0;
	case 1: return nums[0];
	case 2: return std::max(nums[0], nums[1]);
	default: break;
	}

	// 带第一个房子和不带第一个房子
	int has0[2] = { nums[0], std::max(nums[0], nums[1]) };
	int not0[2] = { 0, nums[1] };
	for (int i = 2; i < len; ++i)
	{
		int cur = std::max(has0[1], has0[0] + nums[i]);
		has0[0] = has0[1]; has0[1] = cur;
		cur = std::max(not0[1], not0[0] + nums[i]);
		not0[0] = not0[1]; not0[1] = cur;
	}

	return std::max(has0[0], not0[1]);
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	vector<int> nums = { 1, 2, 3, 1 };
	int ans = rob(nums);
	printf("%1s: %d\n", "rob", ans);
}
