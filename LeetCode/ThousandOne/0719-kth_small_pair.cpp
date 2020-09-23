#include "leetcode.hpp"

/* 719. 找出第 k 小的距离对

给定一个整数数组，返回所有数对之间的第 k 个最小距离。
一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值。

示例 1:
输入：
nums = [1,3,1]
k = 1
输出：0
解释：
所有数对如下：
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
因此第 1 个最小距离的数对是 (1,1)，它们之间的距离为 0。

提示:
	2 <= len(nums) <= 10000.
	0 <= nums[i] < 1000000.
	1 <= k <= len(nums) * (len(nums) - 1) / 2.
*/

int smallestDistancePair(vector<int>& nums, int k)
{
	int len = static_cast<int>(nums.size());
	if (len < 2)
		return 0;

	sort(nums.begin(), nums.end());
	int L = 0, R = nums[len - 1] - nums[0];
	while (L < R)
	{
		int M = (L + R) / 2;
		int N = 0, p = 0, q = 0;
		for (; q < len; ++q)
		{
			while ((p < q) && (nums[q] - nums[p] > M))
				++p;
			N += q - p;
		}
		if (N >= k)
			R = M;
		else
			L = M + 1;
	}
	return L;
}


int main()
{
	vector<int> nums = { 9, 10, 7, 10, 6, 1, 5, 4, 9, 8 };
	OutExpr(smallestDistancePair(nums, 18), "%d");
}
