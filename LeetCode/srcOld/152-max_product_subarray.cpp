#include "../src/utility.hpp"

/** 考虑到负负得正，与求和相比，需要记住一个最小值 */
int maxProduct(vector<int> const& nums)
{
	if (nums.empty()) return 0;

	unsigned len = static_cast<unsigned>(nums.size());
	int maxp = nums[0], minp = nums[0];
	int maxcur = nums[0], mincur = nums[0];
	for (unsigned u = 1u; u < len; ++u)
	{
		maxcur *= nums[u];
		mincur *= nums[u];
		if (mincur > maxcur) std::swap(mincur, maxcur);
		if (mincur > nums[u]) mincur = nums[u];
		else if (maxcur < nums[u]) maxcur = nums[u];
		if (maxp < maxcur) maxp = maxcur;
		if (minp > mincur) minp = mincur;
	}

	return maxp;
}



int main()
{
	vector<int> nums = { 2, 3, -2, 4 };
	int ans = maxProduct(nums);
	printf("%1s = %d\n", "maxProduct", ans);
}
