#include "utility.hpp"


vector<string> summaryRanges(vector<int>& nums)
{
	vector<string> range;
	char buffer[32];
	size_t len = nums.size();
	if (!len) return range;

	size_t left = 0;
	for (size_t i = 1; i < len; ++i)
	{
		if (nums[i - 1u] + 1 == nums[i])
			continue;

		if (left + 1u == i)
			sprintf(buffer, "%d", nums[left]);
		else
			sprintf(buffer, "%d->%d", nums[left], nums[i - 1u]);
		range.push_back(string(buffer));
		left = i;
	}
	if (left + 1u == len)
		sprintf(buffer, "%d", nums[left]);
	else
		sprintf(buffer, "%d->%d", nums[left], nums[len - 1u]);
	range.push_back(string(buffer));

	return range;
}


int main()
{
	vector<int> nums = { 0, 2, 3, 4, 6, 8, 9 };
	vector<string> range = summaryRanges(nums);
	output(range, "; ", "Summary Ranges");
}
