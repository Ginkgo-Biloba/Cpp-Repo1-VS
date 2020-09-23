#include "leetcode.hpp"

/* 1477. 找两个和为目标值且不重叠的子数组

给你一个整数数组 arr 和一个整数值 target 。

请你在 arr 中找 两个互不重叠的子数组 且它们的和都等于 target 。
可能会有多种方案，请你返回满足要求的两个子数组长度和的 最小值 。

请返回满足要求的最小长度和，如果无法找到这样的两个子数组，请返回 -1 。

示例 1：
输入：arr = [3,2,2,4,3], target = 3
输出：2
解释：只有两个子数组和为 3 （[3] 和 [3]）。它们的长度和为 2 。

示例 2：
输入：arr = [7,3,4,7], target = 7
输出：2
解释：尽管我们有 3 个互不重叠的子数组和为 7 （[7], [3,4] 和 [7]），但我们会选择第一个和第三个子数组，因为它们的长度和 2 是最小值。

示例 3：
输入：arr = [4,3,2,6,2,3,4], target = 6
输出：-1
解释：我们只有一个和为 6 的子数组。

示例 4：
输入：arr = [5,5,4,4,5], target = 3
输出：-1
解释：我们无法找到和为 3 的子数组。

示例 5：
输入：arr = [3,1,1,1,5,1,2,1], target = 3
输出：3
解释：注意子数组 [1,2] 和 [2,1] 不能成为一个方案因为它们重叠了。

提示：
	1 <= arr.length <= 10^5
	1 <= arr[i] <= 1000
	1 <= target <= 10^8
*/

// https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/discuss/685470/Python-One-pass-prefix-sum-O(n)/578264
// 抄的
int minSumOfLengths(vector<int>& A, int target)
{
	int len = static_cast<int>(A.size());
	vector<int> buffer(len + 1, INT_MAX);
	int* dp = buffer.data() + 1;
	int ans = INT_MAX;
	int h = 0, i = 0, sum = 0;
	for (; i < len; ++i)
	{
		sum += A[i];
		while (sum > target)
			sum -= A[h++];
		if (sum == target)
		{
			int cur = i - h + 1;
			if ((h > 0) && dp[h - 1] != INT_MAX)
				ans = min(ans, cur + dp[h - 1]);
			dp[i] = min(cur, dp[i - 1]);
		}
		else
			dp[i] = dp[i - 1];
	}
	if (ans == INT_MAX)
		ans = -1;
	return ans;
}


int main()
{
	vector<int>
		a = { 3, 2, 2, 4, 3 },
		b = { 7, 3, 4, 7 },
		c = { 4, 3, 2, 6, 2, 3, 4 },
		d = { 5, 5, 4, 4, 5 },
		e = { 3, 1, 1, 1, 5, 1, 2, 1 };
	OutExpr(minSumOfLengths(a, 3), "%d");
	OutExpr(minSumOfLengths(b, 7), "%d");
	OutExpr(minSumOfLengths(c, 6), "%d");
	OutExpr(minSumOfLengths(d, 3), "%d");
	OutExpr(minSumOfLengths(e, 3), "%d");
}
