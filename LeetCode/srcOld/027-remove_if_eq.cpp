#include <vector>
#include <iostream>

/* 这就真是 remove_if 了 */
int rmDups(std::vector<int>& nums, int const& val)
{
	if (nums.empty()) return 0;
	int ans = 0, sz = static_cast<int>(nums.size());
	for (int i = 0; i < sz; i++)
		if (val != nums[i])
		{
			nums[ans] = nums[i];
			ans++;
		}

	nums.erase(nums.begin() + ans, nums.end());
	return ans;
}



int main()
{
	std::ios::sync_with_stdio(false);
	std::vector<int> nums{ 3, 2, 3, 2};
	int ans = rmDups(nums, 3);
	for (int const& i : nums)
		std::cout << i << "  ";
	std::cout << "\n" << ans << "\n";
	return 0;
}