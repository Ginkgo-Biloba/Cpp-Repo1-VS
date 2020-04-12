#include "leetcode.hpp"

/* 1248. 统计「优美子数组」

给你一个整数数组 nums 和一个整数 k。

如果某个 连续 子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。

请返回这个数组中「优美子数组」的数目。

示例 1：
输入：nums = [1,1,2,1,1], k = 3
输出：2
解释：包含 3 个奇数的子数组是 [1,1,2,1] 和 [1,2,1,1] 。

示例 2：
输入：nums = [2,4,6], k = 1
输出：0
解释：数列中不包含任何奇数，所以不存在优美子数组。

示例 3：
输入：nums = [2,2,2,1,2,2,1,2,2,2], k = 2
输出：16

提示：
	1 <= nums.length <= 50000
	1 <= nums[i] <= 10^5
	1 <= k <= nums.length
*/

int atMost(vector<int> const& A, int k)
{
	int len = static_cast<int>(A.size());
	int h = 0, i = 0, s = 0;
	for (; i < len; ++i)
	{
		k -= (A[i] & 1);
		for (; k < 0; ++h)
			k += (A[h] & 1);
		s += i - h + 1;
	}
	return s;
}

int numberOfSubarrays(vector<int>& nums, int k)
{
	int a = atMost(nums, k);
	int b = atMost(nums, k - 1);
	return a - b;
}


int main()
{
	vector<int>
		a = { 1, 1, 2, 1, 1 },
		b = { 2, 4, 6 },
		c = { 2, 2, 2, 1, 2, 2, 1, 2, 2, 2 };
	OutExpr(numberOfSubarrays(a, 1), "%d");
	OutExpr(numberOfSubarrays(b, 1), "%d");
	OutExpr(numberOfSubarrays(c, 2), "%d");
}
