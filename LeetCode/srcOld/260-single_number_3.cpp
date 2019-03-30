#include "../srcOld/utility.hpp"

/* Given an array of numbers nums,
 * in which exactly two elements appear only once and all the other elements appear exactly twice.
 * Find the two elements that appear only once. */
vector<int> singleNumber(vector<int>& nums)
{
	size_t const len = nums.size();

	int mask = 0;
	for (size_t i = 0; i < len; ++i)
		mask ^= nums[i];

	// 抽出 mask 最后面的那个 1 (其实任意一个 1 都可以)
	// mask & (mask - 1) 将那个 1 变成 0
	mask = mask ^ (mask & (mask - 1));
	vector<int> ans; ans.resize(2, 0);

	for (size_t i = 0; i < len; ++i)
	{
		if (mask & nums[i])
			ans[0] ^= nums[i];
		else
			ans[1] ^= nums[i];
	}

	return ans;
}

int main()
{
	vector<int> nums = { 1, 2, 1, 3, 2, 5 };
	vector<int> ans = singleNumber(nums);
	output(ans, "singleNumber");
}
