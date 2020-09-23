#include "leetcode.hpp"

/* 540. 有序数组中的单一元素

给定一个只包含整数的有序数组，每个元素都会出现两次，唯有一个数只会出现一次，找出这个数。

示例 1:
输入: [1,1,2,3,3,4,4,8,8]
输出: 2

示例 2:
输入: [3,3,7,7,10,11,11]
输出: 10

注意: 您的方案应该在 O(log n)时间复杂度和 O(1)空间复杂度中运行。

*/

// https://leetcode.com/problems/single-element-in-a-sorted-array/discuss/100754/Java-Binary-Search-short-(7l)-O(log(n))-w-explanations
// 抄的
int singleNonDuplicate(vector<int>& nums)
{
	int L = 0, R = static_cast<int>(nums.size());
	if (R < 2)
		return nums[0];
	--R;
	while (L < R)
	{
		int M = L + (R - L) / 2;
		if (M & 1)
			--M;
		if (nums[M] != nums[M + 1])
			R = M;
		else
			L = M + 2;
	}
	return nums[L];
}


int main()
{
	vector<int> nums = { 1, 1, 2, 3, 3, 4, 4, 8, 8 };
	OutExpr(singleNonDuplicate(nums), "%d");
}
