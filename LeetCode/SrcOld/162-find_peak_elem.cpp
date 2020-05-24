#include "leetcode.hpp"

/* 162. 寻找峰值

峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。

数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞。

示例 1:
输入: nums = [1,2,3,1]
输出: 2
解释: 3 是峰值元素，你的函数应该返回其索引 2。

示例 2:
输入: nums = [1,2,1,3,5,6,4]
输出: 1 或 5
解释:
你的函数可以返回索引 1，其峰值元素为 2；
或者返回索引 5， 其峰值元素为 6。

说明:
你的解法应该是 O(logN) 时间复杂度的。
*/

// https://leetcode.com/problems/find-peak-element/discuss/50232/Find-the-maximum-by-binary-search-(recursion-and-iteration)
// 抄的
int findPeakElement(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int a = 0, b = len - 1, m, n;
	while (a < b)
	{
		m = (a + b) / 2;
		n = m + 1;
		if (A[m] < A[n])
			a = n;
		else
			b = m;
	}
	return a;
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 1 },
		b = { 1, 2, 1, 3, 5, 6, 4 };
	OutExpr(findPeakElement(a), "%d");
	OutExpr(findPeakElement(b), "%d");
}
