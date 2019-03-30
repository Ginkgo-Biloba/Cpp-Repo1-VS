#include "utility.hpp"

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
	vector<pair<int64_t, int>> validx;
	int const len = static_cast<int>(nums.size());
	int64_t const dval = t, didx = k;

	for (int i = 0; i < len; ++i)
		validx.emplace_back(nums[i], i);
	std::sort(validx.begin(), validx.end());

	for (int i = 0; i < len; ++i)
	{
		pair<int64_t, int> cur = validx[i];
		for (int h = i + 1; h < len; ++h)
		{
			pair<int64_t, int> vih = validx[h];
			if (vih.first - cur.first > dval)
				break;
			if (std::abs(vih.second - cur.second) <= didx)
				return true;
		}
	}
	return false;
}


int main()
{
	vector<int> nums = { 1, 5, 9, 1, 5, 9 };
	bool ans = containsNearbyAlmostDuplicate(nums, 2, 3);
	printf("containsNearbyAlmostDuplicate = %d\n", ans);
}
