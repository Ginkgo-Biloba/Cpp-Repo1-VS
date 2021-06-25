#include "leetcode.hpp"

/* 1787. 使所有区间的异或结果为零

给你一个整数数组 nums​​​ 和一个整数 k​​​​​ 。区间 [left, right]（left <= right）的 异或结果 是对下标位于 left 和 right（包括 left 和 right ）之间所有元素进行 XOR 运算的结果：nums[left] XOR nums[left+1] XOR ... XOR nums[right] 。

返回数组中 要更改的最小元素数 ，以使所有长度为 k 的区间异或结果等于零。

示例 1：
输入：nums = [1,2,0,3,0], k = 1
输出：3
解释：将数组 [1,2,0,3,0] 修改为 [0,0,0,0,0]

示例 2：
输入：nums = [3,4,5,2,1,7,3,4,7], k = 3
输出：3
解释：将数组 [3,4,5,2,1,7,3,4,7] 修改为 [3,4,7,3,4,7,3,4,7]

示例 3：
输入：nums = [1,2,4,1,2,5,1,2,6], k = 3
输出：3
解释：将数组[1,2,4,1,2,5,1,2,6] 修改为 [1,2,3,1,2,3,1,2,3]

提示：
	1 <= k <= nums.length <= 2000
	​​​​​​0 <= nums[i] < 2^10
*/

// https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/discuss/1097537/Explanation-of-DP-Approach-%2B-Code-(C%2B%2B)
// 抄的
int minChanges(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());

	vector<array<int, 1024>> freq(k);
	memset(freq.data(), 0, k * sizeof(freq[0]));
	for (int i = 0; i < len; ++i)
		freq[i % k][A[i]] += 1;

	vector<array<int, 1024>> dp(k + 1);
	memset(dp.data(), 0x3f, (k + 1) * sizeof(dp[0]));
	dp[0][0] = 0;

	// 目前为止，异或得到任何值得需要的最少改变
	int prev = 0;
	for (int i = 0; i < k; ++i)
	{
		// 尝试 0-1024 每个数字
		for (int j = 0; j < 1024; ++j)
			for (int m = i; m < len; m += k)
			{
				dp[i + 1][j ^ A[m]] = min(
					dp[i + 1][j ^ A[m]],
					dp[i][j] + (len - i + k - 1) / k - freq[i][A[m]]);
			}
		int curr = INT_MAX;
		for (int j = 0; j < 1024; ++j)
		{
			dp[i + 1][j] = min(dp[i + 1][j],
				(len - i + k - 1) / k + prev);
			curr = min(curr, dp[i + 1][j]);
		}
		prev = curr;
	}
	return dp[k][0];
}


int main()
{
	vector<int>
		a = { 1, 2, 0, 3, 0 },
		b = { 3, 4, 5, 2, 1, 7, 3, 4, 7 },
		c = { 1, 2, 4, 1, 2, 5, 1, 2, 6 };
	OutExpr(minChanges(a, 1), "%d");
	OutExpr(minChanges(b, 3), "%d");
	OutExpr(minChanges(c, 3), "%d");
}
