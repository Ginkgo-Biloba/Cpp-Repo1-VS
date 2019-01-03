#include "../src/utility.hpp"


int removeDuplicates(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	if (len < 3) return len;

	int l = 1, r, c = 1;
	for (; l < len; ++l)
	{
		if (nums[l] == nums[l - 1])
			break;
	}
	for (r = l + 1; r < len; ++r)
	{
		if (nums[r] == nums[r - 1])
		{
			++c;
			if (c > 1) continue;
		}
		else c = 0;
		++l; nums[l] = nums[r];
	}

	if (l < len) ++l;
	nums.erase(nums.begin() + l, nums.end());
	return l;
}


int main()
{
	vector<int> digits = { 1, 1, 1, 2, 2, 5, 5, 5 };
	removeDuplicates(digits);
	output(digits, "removeDuplicates");
}
