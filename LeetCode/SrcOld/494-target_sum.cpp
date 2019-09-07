#include "leetcode.hpp"

/* 494. 目标和

给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。

返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

示例 1:

输入: nums: [1, 1, 1, 1, 1], S: 3
输出: 5
解释:

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

一共有5种方法让最终目标和为3。

注意:

		数组的长度不会超过20，并且数组中的值全为正数。
		初始的数组的和不会超过1000。
		保证返回的最终结果为32位整数。
*/

// https://leetcode.com/problems/reverse-pairs/discuss/97268/General-principles-behind-problems-similar-to-%22Reverse-Pairs%22
// DFS 还好，但是这里是抄的，竟然能转换成背包问题
int findTargetSumWays(vector<int>& nums, int S)
{
	int sum = 0;
	int len = static_cast<int>(nums.size());
	for (int i = 0; i < len; ++i)
		sum += nums[i];
	if ((sum < S) || ((sum + S) % 2 != 0))
		return 0;

	S = (S + sum) / 2;
	vector<int> dp(S + 1);
	dp[0] = 1;
	for (int i = 0; i < len; ++i)
	{
		int n = nums[i];
		for (int s = S; s >= n; --s)
			dp[s] += dp[s - n];
	}
	return dp[S];
}


int main()
{
	vector<int> nums = { 1, 1, 1, 1, 1 };
	OutExpr(findTargetSumWays(nums, 3), "%d");
}
