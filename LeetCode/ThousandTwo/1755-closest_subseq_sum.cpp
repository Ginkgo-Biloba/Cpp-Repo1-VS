#include "leetcode.hpp"

/* 1755. 最接近目标值的子序列和

给你一个整数数组 nums 和一个目标值 goal 。

你需要从 nums 中选出一个子序列，使子序列元素总和最接近 goal 。
也就是说，如果子序列元素和为 sum ，你需要 最小化绝对差 abs(sum - goal) 。

返回 abs(sum - goal) 可能的 最小值 。

注意，数组的子序列是通过移除原始数组中的某些元素（可能全部或无）而形成的数组。

示例 1：
输入：nums = [5,-7,3,5], goal = 6
输出：0
解释：选择整个数组作为选出的子序列，元素和为 6 。
子序列和与目标值相等，所以绝对差为 0 。

示例 2：
输入：nums = [7,-9,15,-2], goal = -5
输出：1
解释：选出子序列 [7,-9,-2] ，元素和为 -4 。
绝对差为 abs(-4 - (-5)) = abs(1) = 1 ，是可能的最小值。

示例 3：
输入：nums = [1,2,3], goal = -7
输出：7

提示：
	1 <= nums.length <= 40
	-10^7 <= nums[i] <= 10^7
	-10^9 <= goal <= 10^9
*/

// 看的提示
class Solution
{
	vector<int> A, B;

	void subset(int const* ptr, int len, vector<int>& out)
	{
		int mask = 1 << len;
		out.reserve(mask);
		out.assign(1, 0);
		for (--mask; mask >= 0; --mask)
		{
			int cur = 0;
			for (int i = 0; i < len; ++i)
			{
				if ((1 << i) & mask)
					cur += ptr[i];
			}
			out.push_back(cur);
		}
		sort(out.begin(), out.end());
		out.erase(unique(out.begin(), out.end()), out.end());
	}

public:
	int minAbsDifference(vector<int>& nums, int goal)
	{
		int len = static_cast<int>(nums.size());
		int ans = abs(goal);
		subset(nums.data(), len / 2, A);
		subset(nums.data() + len / 2, len - len / 2, B);
		for (int a : A)
		{
			int b = goal - a;
			auto it = upper_bound(B.begin(), B.end(), b);
			if (it != B.end())
				ans = min(ans, (*it) - b);
			if (it != B.begin())
				ans = min(ans, b - *(--it));
		}
		return ans;
	}
};


int main()
{
	vector<int>
		a = { 5, -7, 3, 5 },
		b = { 7, -9, 15, -2 },
		c = { 1, 2, 3 };
	Solution s;
	OutExpr(s.minAbsDifference(a, 6), "%d");
	OutExpr(s.minAbsDifference(b, -5), "%d");
	OutExpr(s.minAbsDifference(c, -7), "%d");
}
