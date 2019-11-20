#include "leetcode.hpp"

/* 327. 区间和的个数
* 给定一个整数数组 nums，返回区间和在 [lower, upper] 之间的个数，包含 lower 和 upper。
* 区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)。
* 说明：最直观的算法复杂度是 O(n^2) ，请在此基础上优化你的算法。
*/

// https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/138154/The-C%2B%2B-merge-sort-template-for-pairs-'i'-'j'-problem
// 抄的
class Solution
{
	vector<int64_t> acc;
	size_t len;
	int ans;
	int64_t lower, upper;

	void sortCount(int left, int right)
	{
		if (right - left <= 1)
			return;
		
		int mid = (left + right) / 2;
		sortCount(left, mid);
		sortCount(mid, right);

		int L = left, M = mid, R = mid;
		for (; L < mid; ++L)
		{
			while (M < right && (acc[M] - acc[L] < lower)) ++M;
			while (R < right && (acc[R] - acc[L] <= upper)) ++R;
			ans += R - M;
		}
		std::inplace_merge(acc.begin() + left, acc.begin() + mid, acc.begin() + right);
	}
public:

	int countRangeSum(vector<int>& nums, int _lower, int _upper)
	{
		ans = 0;
		len = nums.size();
		lower = _lower; upper = _upper;

		if (acc.size() < len + 1)
			acc.resize(len + 1, 0);
		acc[0] = 0;
		for (size_t i = 0; i < len; ++i)
			acc[i + 1] = acc[i] + nums[i];

		sortCount(0, static_cast<int>(len) + 1);
		return ans;
	}
};


int main()
{
	vector<int> nums = { -2, 5, -1 };
	int lower = -2, upper = 2;
	int count = Solution().countRangeSum(nums, lower, upper);
	printf("countRangeSum: %d\n", count);
}