#include <vector>
#include <iostream>

/* 跟 remove_if 没多大区别 */
int rmDups(std::vector<int>& nums)
{
	if (nums.empty()) return 0;
	int ans = 0, sz = static_cast<int>(nums.size());
	int i, prev = nums[0];
	for (i = 1; i < sz; i++)
		if (prev != nums[i])
		{
			prev = nums[i];
			ans++;	nums[ans] = prev;
		}

	ans++;
	nums.erase(nums.begin() + ans, nums.end());
	return ans;
}



int main()
{
	std::ios::sync_with_stdio(false);
	std::vector<int> nums{ 1, 1, 2 };
	int ans = rmDups(nums);
	for (int const& i : nums)
		std::cout << i << "  ";
	std::cout << "\n" << ans << "\n";
	return 0;
}