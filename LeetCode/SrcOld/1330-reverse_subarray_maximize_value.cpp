#include "leetcode.hpp"

/* 1330. 翻转子数组得到最大的数组值

给你一个整数数组 nums 。「数组值」定义为所有满足 0 <= i < nums.length-1 的 |nums[i]-nums[i+1]| 的和。

你可以选择给定数组的任意子数组，并将该子数组翻转。但你只能执行这个操作 一次 。

请你找到可行的最大 数组值 。

示例 1：
输入：nums = [2,3,1,5,4]
输出：10
解释：通过翻转子数组 [3,1,5] ，数组变成 [2,5,1,3,4] ，数组值为 10 。

示例 2：
输入：nums = [2,4,9,24,2,1,10]
输出：68

提示：
	1 <= nums.length <= 3*10^4
	-10^5 <= nums[i] <= 10^5
*/

// https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/discuss/489882/O(n)-Solution-with-explanation
// 抄的
int maxValueAfterReverse(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int sum = 0, delta = 0;
	for (int i = 1; i < len; ++i)
		sum += abs(A[i - 1] - A[i]);

	int cd = INT_MIN, ab = INT_MAX;
	for (int i = 1; i < len; ++i)
	{
		cd = max(cd, min(A[i - 1], A[i]));
		ab = min(ab, max(A[i - 1], A[i]));
	}
	delta = max(delta, (cd - ab) * 2);

	cd = ab = 0;
	for (int i = 1; i < len; ++i)
	{
		cd = abs(A[0] - A[i]) - abs(A[i - 1] - A[i]);
		ab = abs(A[len - 1] - A[i - 1]) - abs(A[i - 1] - A[i]);
		delta = max(delta, max(ab, cd));
	}

	return sum + delta;
}


int main()
{
	vector<int>
		a = { 2, 3, 1, 5, 4 },
		b = { 2, 4, 9, 24, 2, 1, 10 },
		c = { 63674, -34608, 86424, -52056, -3992, 93347, 2084, -28546, -75702, -28400 };
	OutExpr(maxValueAfterReverse(a), "%d");
	OutExpr(maxValueAfterReverse(b), "%d");
	OutExpr(maxValueAfterReverse(c), "%d");
}
