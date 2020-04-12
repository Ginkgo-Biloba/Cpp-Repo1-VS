#include "leetcode.hpp"

/* 1262. 可被三整除的最大和

给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。

示例 1：
输入：nums = [3,6,5,1,8]
输出：18
解释：选出数字 3, 6, 1 和 8，它们的和是 18（可被 3 整除的最大和）。

示例 2：
输入：nums = [4]
输出：0
解释：4 不能被 3 整除，所以无法选出数字，返回 0。

示例 3：
输入：nums = [1,2,3,4,4]
输出：12
解释：选出数字 1, 3, 4 以及 4，它们的和是 12（可被 3 整除的最大和）。

提示：
	1 <= nums.length <= 4 * 10^4
	1 <= nums[i] <= 10^4
*/

// https://leetcode.com/problems/greatest-sum-divisible-by-three/discuss/431077/JavaC%2B%2BPython-One-Pass-O(1)-space
// 抄的
int maxSumDivThree(vector<int>& nums)
{
	array<int, 3> A = { 0, 0, 0 }, B;
	memset(A.data(), 0, sizeof(A));
	for (int n : nums)
	{
		B = A;
		for (int i : B)
			A[(i + n) % 3] = max(A[(i + n) % 3], i + n);
	}
	return A[0];
}


int main()
{
	vector<int>
		a = { 3, 6, 5, 1, 8 },
		b = { 4 },
		c = { 1, 2, 3, 4, 4 };
	OutExpr(maxSumDivThree(a), "%d");
	OutExpr(maxSumDivThree(b), "%d");
	OutExpr(maxSumDivThree(c), "%d");
}
