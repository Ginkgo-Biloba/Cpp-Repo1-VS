#include <vector>
#include <cstdio>
#include <algorithm>
using std::vector;

/** 没有重复元素 */
int findMin1(vector<int> const& nums, unsigned l, unsigned r)
{
	int ans;
	unsigned m = r - l;
	if (m <= 1u)
		return nums[l];
	if (m == 2u)
		return std::min(nums[l], nums[l + 1u]);
	if (m == 3u)
		return std::min(std::min(nums[l], nums[l + 1u]), nums[l + 2u]);

	m = (r + l) / 2u;
	if ((nums[l] < nums[m]) && (nums[m] < nums[r - 1u]))
		ans = nums[l];
	else if (nums[m - 1u] > nums[m])
		ans = nums[m];
	else if (nums[l] < nums[m])
		ans = findMin1(nums, m + 1u, r);
	else
		ans = findMin1(nums, l, m);
	return ans;
}

/** 同上，不提前结束 */
int findMin11(vector<int> const& nums, unsigned l, unsigned r)
{
	--r;
	while (l < r)
	{
		unsigned m = (r + l) / 2;
		if (nums[m] < nums[r])
			r = m;
		else
			l = m + 1u;
	}
	return nums[l];
}


/** 有重复元素 */
int findMin2(vector<int> const& nums, unsigned l, unsigned r)
{
	unsigned m = r - l;
	if (m == 1u) return nums[l];
	if (m == 2u) return std::min(nums[l], nums[l + 1u]);

	--r;
	while (l < r)
	{
		m = (r + l) / 2u;
		if ((nums[l] < nums[m]) && (nums[m] <= nums[r]))
			return nums[l];
		if ((l != m) && (nums[m - 1u] > nums[m]))
			return nums[m];
		if (nums[l] < nums[m])
			l = m + 1u;
		else if (nums[m] < nums[r])
			r = m;
		else if (nums[r] == nums[m])
			--r;
		else // if (nums[l] == nums[m])
			++l;
	}

	return nums[l];
}

/** 同上，不提前结束 */
int findMin22(vector<int> const& nums, unsigned l, unsigned r)
{
	--r;
	while (l < r)
	{
		unsigned m = (r + l) / 2u;
		if (nums[m] < nums[r])
			r = m;
		else if (nums[m] > nums[r])
			l = m + 1u;
		else
			--r;
	}
	return nums[l];
}


int findMin(vector<int>& nums)
{
	unsigned len = static_cast<unsigned>(nums.size());
	if (len == 1u) return nums[0];
	return findMin2(nums, 0u, len);
}


int main()
{
	vector<int> nums = { 3, 3, 1, 3 };
	int ans = findMin(nums);
	printf("%1s = %d\n", "findMin", ans);
}
