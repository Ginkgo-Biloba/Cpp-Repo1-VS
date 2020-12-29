#include "leetcode.hpp"

/* 1703. 得到连续 K 个 1 的最少相邻交换次数

给你一个整数数组 nums 和一个整数 k 。
nums 仅包含 0 和 1 。
每一次移动，你可以选择 相邻 两个数字并将它们交换。

请你返回使 nums 中包含 k 个 连续 1 的 最少 交换次数。

示例 1：
输入：nums = [1,0,0,1,0,1], k = 2
输出：1
解释：在第一次操作时，nums 可以变成 [1,0,0,0,1,1] 得到连续两个 1 。

示例 2：
输入：nums = [1,0,0,0,0,0,1,1], k = 3
输出：5
解释：通过 5 次操作，最左边的 1 可以移到右边直到 nums 变为 [0,0,0,0,0,1,1,1] 。

示例 3：
输入：nums = [1,1,0,1], k = 2
输出：0
解释：nums 已经有连续 2 个 1 了。

提示：
	1 <= nums.length <= 10^5
	nums[i] 要么是 0 ，要么是 1 。
	1 <= k <= sum(nums)
*/

// https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/discuss/987347/JavaC%2B%2BPython-Solution
// 抄的
int minMoves1(vector<int>& nums, int k)
{
	int len = static_cast<int>(nums.size());
	vector<int> one;
	for (int i = 0; i < len; ++i)
	{
		if (nums[i])
			one.push_back(i);
	}
	len = static_cast<int>(one.size());
	vector<int64_t> pre(len + 1);
	for (int i = 0; i < len; ++i)
		pre[i + 1] = pre[i] + one[i];
	int64_t ans = INT_MAX;
	for (int i = 0; i < len - k + 1; ++i)
	{
		int m1 = k / 2 + i;
		int m2 = (k + 1) / 2 + i;
		ans = min(ans, pre[i + k] - pre[m1] - pre[m2] + pre[i]);
	}
	ans -= (k / 2) * ((k + 1 / 2));
	return static_cast<int>(ans);
}

// https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/discuss/987607/O(n)-explanation-with-picture
// 抄的
int minMoves(vector<int>& nums, int k)
{
	int len = static_cast<int>(nums.size());
	vector<int> one;
	for (int i = 0; i < len; ++i)
	{
		if (nums[i])
			one.push_back(i);
	}
	len = static_cast<int>(one.size());
	vector<int64_t> pre(len + 1);
	for (int i = 0; i < len; ++i)
		pre[i + 1] = pre[i] + one[i];
	int64_t ans = INT_MAX;
	for (int a = 1, b = k; b <= len; ++a, ++b)
	{
		int mid = (a + b) / 2;
		int64_t rad = mid - a;
		int64_t right = pre[b] - pre[mid];
		int64_t left = pre[mid - 1] - pre[a - 1];
		int64_t sub = rad * (rad + 1);
		if (k % 2 == 0)
		{
			left += one[mid - 1];
			sub += rad + 1;
		}
		ans = min(ans, right - left - sub);
	}
	return static_cast<int>(ans);
}

int main()
{}
