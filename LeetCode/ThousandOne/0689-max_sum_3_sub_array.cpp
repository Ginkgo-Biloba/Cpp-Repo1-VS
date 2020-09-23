#include "leetcode.hpp"

/* 689. 三个无重叠子数组的最大和

给定数组 nums 由正整数组成，找到三个互不重叠的子数组的最大和。
每个子数组的长度为k，我们要使这3*k个项的和最大化。
返回每个区间起始索引的列表（索引从 0 开始）。如果有多个结果，返回字典序最小的一个。

示例:

输入: [1,2,1,2,6,7,5,1], 2
输出: [0, 3, 5]
解释: 子数组 [1, 2], [2, 6], [7, 5] 对应的起始索引为 [0, 3, 5]。
我们也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。

注意:
	nums.length的范围在[1, 20000]之间。
	nums[i]的范围在[1, 65535]之间。
	k的范围在[1, floor(nums.length / 3)]之间。
*/

// https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/discuss/108231/C%2B%2BJava-DP-with-explanation-O(n)
// 抄的
vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
{
	int len = static_cast<int>(nums.size());
	int maxsum = 0;
	vector<int> sum(len + 1, 0), left(len, 0), right(len, len - k), ans(3, 0);
	for (int i = 0; i < len; ++i)
		sum[i + 1] = sum[i] + nums[i];
	// starting index of the left max sum interval
	// 以 i 开头的 k 个数字的最大值
	for (int i = k, tot = sum[k] - sum[0]; i < len; ++i)
		if (sum[i + 1] - sum[i - k + 1] > tot)
		{
			left[i] = i - k + 1;
			tot = sum[i + 1] - sum[i - k + 1];
		}
		else
			left[i] = left[i - 1];
	// starting index of the right max sum interval
	// the condition is ">= tot" for right interval, and "> tot" for left interval
	// 以 i 开头的 k 个数字的最大值
	for (int i = len - k - 1, tot = sum[len] - sum[len - k];
			i >= 0; --i)
		if (sum[i + k] - sum[i] >= tot)
		{
			right[i] = i;
			tot = sum[i + k] - sum[i];
		}
		else
			right[i] = right[i + 1];
	// test all possible middle interval
	// 测试所有间隔
	for (int i = k; i <= len - 2 * k; ++i)
	{
		int L = left[i - 1], R = right[i + k];
		int tot = (sum[L + k] - sum[L])
			+ (sum[i + k] - sum[i]) + (sum[R + k] - sum[R]);
		if (tot > maxsum)
		{
			maxsum = tot;
			ans[0] = L;
			ans[1] = i;
			ans[2] = R;
		}
	}
	return ans;
}


int main()
{
	vector<int> nums = { 1, 2, 1, 2, 6, 7, 5, 1 };
	output(maxSumOfThreeSubarrays(nums, 2),
		"Maximum Sum of 3 Non-Overlapping Subarrays");
}
