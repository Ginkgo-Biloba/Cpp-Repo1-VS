#include "../srcOld/utility.hpp"

// 312. Burst Balloons
// https://leetcode.com/problems/burst-balloons/discuss/76230/C%2B%2B-dp-detailed-explanation
// 抄的
int maxCoins(vector<int>& nums)
{
	int const n = static_cast<int>(nums.size()) + 2;
	vector<vector<int>> dp(n, vector<int>(n, 0));
	nums.reserve(n);
	nums.push_back(1);
	std::reverse(nums.begin(), nums.end());
	nums.push_back(1);

	for (int k = 2; k < n; ++k)
		for (int left = 0; left < n - k; ++left)
		{
			int right = left + k;
			for (int i = left + 1; i < right; ++i)
				dp[left][right] = std::max(dp[left][right],
					nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
		}

	return dp[0][n - 1];
}


int main()
{
	vector<int> nums = { 3, 1, 5, 8 };
	int ans = maxCoins(nums);
	printf("maxCoins: %d\n", ans);
}

