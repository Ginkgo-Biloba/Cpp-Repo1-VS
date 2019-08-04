#include "leetcode.hpp"

// 抄的
int lengthOfLIS(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	vector<int> res;
	res.reserve(len);

	for (int i = 0; i < len; ++i)
	{
		int val = nums[i];
		vector<int>::iterator it = std::lower_bound(res.begin(), res.end(), val);
		if (it == res.end())
			res.push_back(val);
		else
			*it = val;
	}

	return static_cast<int>(res.size());
}



int main()
{
	vector<int> nums = { 10, 9, 2, 5, 3, 7, 101, 18 };
	int n = lengthOfLIS(nums);
	printf("Longest Increasing Subsequence: %d\n", n);
}
