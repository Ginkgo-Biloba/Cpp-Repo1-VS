#include "leetcode.hpp"

/* 1567. 乘积为正数的最长子数组长度

给你一个整数数组 nums ，请你求出乘积为正数的最长子数组的长度。

一个数组的子数组是由原数组中零个或者更多个连续数字组成的数组。

请你返回乘积为正数的最长子数组长度。

示例  1：
输入：nums = [1,-2,-3,4]
输出：4
解释：数组本身乘积就是正数，值为 24 。

示例 2：
输入：nums = [0,1,-2,-3,-4]
输出：3
解释：最长乘积为正数的子数组为 [1,-2,-3] ，乘积为 6 。
注意，我们不能把 0 也包括到子数组中，因为这样乘积为 0 ，不是正数。

示例 3：
输入：nums = [-1,-2,-3,0,1]
输出：2
解释：乘积为正数的最长子数组是 [-1,-2] 或者 [-2,-3] 。

示例 4：
输入：nums = [-1,2]
输出：1

示例 5：
输入：nums = [1,2,3,5,-6,4,0,10]
输出：4

提示：
	1 <= nums.length <= 10^5
	-10^9 <= nums[i] <= 10^9
*/

int getMaxLen(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int neg = len, pos = -1;
	int ans = 0, cur = 1;
	for (int i = 0; i < len; ++i)
	{
		if (A[i] == 0)
		{
			neg = len;
			pos = i;
			cur = 1;
			continue;
		}
		cur *= (A[i] > 0 ? 1 : -1);
		if (cur > 0)
			ans = max(ans, i - pos);
		else
		{
			neg = min(neg, i);
			ans = max(ans, i - neg);
		}
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 1, -2, -3, 4 },
		b = { 0, 1, -2, -3, -4 },
		c = { -1, -2, -3, 0, 1 },
		d = { -1, 2 },
		e = { 1, 2, 3, 5, -6, 4, 0, 10 },
		f = { -1, -2 };
	OutExpr(getMaxLen(a), "%d");
	OutExpr(getMaxLen(b), "%d");
	OutExpr(getMaxLen(c), "%d");
	OutExpr(getMaxLen(d), "%d");
	OutExpr(getMaxLen(e), "%d");
	OutExpr(getMaxLen(f), "%d");
}
