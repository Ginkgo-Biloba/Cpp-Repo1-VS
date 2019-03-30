#include <cstdio>
#include <vector>
#include <algorithm>

int maximumGap1(std::vector<int>& nums)
{
	size_t const len = nums.size();
	if (len < 2) return 0;

	std::sort(nums.begin(), nums.end());
	int ans = nums[1] - nums[0];
	for (size_t i = 2; i < len; i++)
	{
		int cur = nums[i] - nums[i - 1u];
		if (ans < cur) ans = cur;
	}
	return ans;
}


int maximumGap2(std::vector<int>& nums)
{
	size_t const len = nums.size();
	if (len < 2) return 0;
	int ans = 0;



	return ans;
}


int main()
{
	std::vector<int> nums = {};
	int ans = maximumGap2(nums);
	printf("ans = %d\n", ans);
	return 0;
}
