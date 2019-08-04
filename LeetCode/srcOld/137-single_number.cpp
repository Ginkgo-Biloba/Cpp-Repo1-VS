#include "leetcode.hpp"

/** 除了一个数出现一次，其他的都出现 3 次 */
int singleNumber(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	int ans = 0;

	int const bits = sizeof(int) * 8;
	int ptr[bits] = { 0 };

	for (int i = 0; i < len; ++i)
	{
		int cur = nums[i], mask = 1;
		for (int b = 0; b < bits; ++b)
		{
			if (cur & mask)
				ptr[b] += 1;
			mask <<= 1;
		}
	}

	for (int b = 0; b < bits; ++b)
	{
		if (ptr[b] % 3)
			ans |= (1 << b);
	}

	return ans;
}


int main()
{
	vector<int> nums = { 0, 1, 0, 1, 0, 1, 99 };
	int ans = singleNumber(nums);
	printf("%1s = %d\n", "singleNumber", ans);
}
