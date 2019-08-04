#include "leetcode.hpp"


int rob(vector<int> const& nums)
{
	int prev2 = 0, prev1 = 0;
	int const len = static_cast<int>(nums.size());
	if (len == 0) return 0;

	for (int i = 0; i < len; ++i)
	{
		int cur = std::max(prev1, prev2 + nums[i]);
		prev2 = prev1;
		prev1 = cur;
	}
	return std::max(prev2, prev1);
}



/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	vector<int> nums = { 2, 7, 9, 3, 1 };
	int ans = ::rob(nums);
	printf("%1s: %d\n", "rob", ans);
}
