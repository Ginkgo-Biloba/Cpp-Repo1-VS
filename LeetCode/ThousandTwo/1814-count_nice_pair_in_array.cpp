#include "leetcode.hpp"

/* 1814. 统计一个数组中好对子的数目

给你一个数组 nums ，数组中只包含非负整数。

定义 rev(x) 的值为将整数 x 各个数字位反转得到的结果。
比方说 rev(123) = 321 ， rev(120) = 21 。

我们称满足下面条件的下标对 (i, j) 是 好的 ：
	0 <= i < j < nums.length
	nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])

请你返回好下标对的数目。
由于结果可能会很大，请将结果对 10^9 + 7 取余 后返回。

示例 1：
输入：nums = [42,11,1,97]
输出：2
解释：两个坐标对为：
 - (0,3)：42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121 。
 - (1,2)：11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12 。

示例 2：
输入：nums = [13,10,35,24,76]
输出：4

提示：
	1 <= nums.length <= 10^5
	0 <= nums[i] <= 10^9
*/

int countNicePairs(vector<int>& A)
{
	int64_t const mod = static_cast<int64_t>(1e9 + 7);
	int len = static_cast<int>(A.size());
	for (int i = 0; i < len; ++i)
	{
		int b = 0;
		for (int c = A[i]; c; c /= 10)
			b = b * 10 + c % 10;
		A[i] -= b;
	}

	int pre = 0;
	int64_t ans = 0;
	sort(A.begin(), A.end());
	for (int i = 1; i <= len; ++i)
	{
		if (i < len && A[pre] == A[i])
			continue;
		int64_t d = i - pre;
		ans = ans + d * (d - 1) / 2;
		pre = i;
	}
	return static_cast<int>(ans % mod);
}


int main()
{
	vector<int>
		a = { 42, 11, 1, 97 },
		b = { 13, 10, 35, 24, 76 };
	OutExpr(countNicePairs(a), "%d");
	OutExpr(countNicePairs(b), "%d");
}
