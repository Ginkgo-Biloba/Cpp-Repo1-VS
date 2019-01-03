#include "../src/utility.hpp"

int majorityElement(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	if (len < 3) return nums[0];

	int prev = nums[0], cnt = 1;
	for (int i = 1; i < len; ++i)
	{
		int cur = nums[i];
		if (cur == prev)
			++cnt;
		else
		{
			if (cnt != 0) --cnt;
			else { prev = cur; cnt = 1; }
		}
	}
	return prev;
}


int main()
{
	vector<int> nums = { 2, 2, 1, 1, 1, 2, 2 };
	int ans = majorityElement(nums);
	printf("%1s = %d\n", "majorityElement", ans);
}
