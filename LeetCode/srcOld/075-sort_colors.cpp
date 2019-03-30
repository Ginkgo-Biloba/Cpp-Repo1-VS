#include "../srcOld/utility.hpp"

void sortColors(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	if (len < 2) return;

	int n0 = -1, n1 = -1, n2 = -1;
	for (int i = 0; i < len; ++i)
	{
		switch (nums[i])
		{
		case 2: nums[++n2] = 2; break;
		case 1: nums[++n2] = 2; nums[++n1] = 1; break;
		default:
		case 0: nums[++n2] = 2; nums[++n1] = 1; nums[++n0] = 0;
		}
	}
}


int main()
{
	vector<int> digits = { 2, 0, 1, 0 };
	sortColors(digits);
	output(digits, "sortColors");
}
