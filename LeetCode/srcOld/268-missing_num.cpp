#include "leetcode.hpp"

int missingNumber(vector<int>& nums)
{
	size_t const len = nums.size();
	int mask = static_cast<int>(len);

	// mask 异或 0 到 len，然后异或所有数字，跟 single number 1 一样
	for (size_t i = 0; i < len; ++i)
	{
		mask ^= i;
		mask ^= nums[i];
	}

	return mask;
}

int main()
{
	vector<int> nums = { 9, 6, 4, 2, 3, 5, 7, 0, 1 };
	int n = missingNumber(nums);
	printf("missingNumber: %d\n", n);
}
