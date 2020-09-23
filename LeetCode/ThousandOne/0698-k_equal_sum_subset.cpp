#include "leetcode.hpp"

/* 698. 划分为k个相等的子集

给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。

示例 1：
输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
输出： True
说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。

注意:
	1 <= k <= len(nums) <= 16
	0 < nums[i] < 10000
*/

// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/discuss/140541/Clear-explanation-easy-to-understand-C%2B%2B-%3A-4ms-beat-100
// 抄的
class Solution
{
	int mean, len, k;
	vector<int> nums, bucket;

	bool put(int n)
	{
		int cur = nums[n];
		for (int i = 0; i < k; ++i)
		{
			if (bucket[i] + cur > mean)
				continue;
			bucket[i] += cur;
			if (n == len - 1)
				return true;
			if (put(n + 1))
				return true;
			bucket[i] -= cur;
			// 不需要尝试其他的空桶
			if (bucket[i] == 0)
				return false;
		}
		return false;
	}

public:
	bool canPartitionKSubsets(vector<int>& _nums, int _k)
	{
		nums.swap(_nums);
		k = _k;
		mean = 0;
		len = static_cast<int>(nums.size());
		for (int i = 0; i < len; ++i)
			mean += nums[i];
		if (mean % k)
			return false;
		mean /= k;
		// 先尝试大的数字，更靠近上层剪枝
		sort(nums.begin(), nums.end(), std::greater<int>());
		if (bucket.size() < static_cast<unsigned>(k))
			bucket.resize(k);
		memset(bucket.data(), 0, k * sizeof(int));
		return put(0);
	}
};


int main()
{
	vector<int> nums = { 4, 3, 2, 3, 5, 2, 1 };
	Solution s;
	OutBool(s.canPartitionKSubsets(nums, 4));
}
