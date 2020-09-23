#include "leetcode.hpp"

/* 414. 第三大的数

给定一个非空数组，返回此数组中第三大的数。如果不存在，则返回数组中最大的数。要求算法时间复杂度必须是O(n)。

示例 1:
输入: [3, 2, 1]
输出: 1
解释: 第三大的数是 1.

示例 2:
输入: [1, 2]
输出: 2
解释: 第三大的数不存在, 所以返回最大的数 2 .

示例 3:
输入: [2, 2, 3, 1]
输出: 1

解释: 注意，要求返回第三大的数，是指第三大且唯一出现的数。
存在两个值为2的数，它们都排第二。
*/


// 抄的
int thirdMax(vector<int>& nums)
{
	int a[3] = { INT_MIN, INT_MIN, INT_MIN };
	bool hasmin = false;
	for (int i : nums)
	{
		if (i == INT_MIN)
			hasmin = true;
		if (i <= a[0] || i == a[1] || i == a[2])
			continue;

		if (i > a[2])
		{
			a[0] = a[1];
			a[1] = a[2];
			a[2] = i;
		}
		else if (i > a[1])
		{
			a[0] = a[1];
			a[1] = i;
		}
		else if (i >= a[0])
			a[0] = i;
	}
	if (hasmin)
		return a[1] == INT_MIN ? a[2] : a[0];
	else
		return a[0] == INT_MIN ? a[2] : a[0];
}


int main()
{
	vector<int> nums = { 1, 2, INT_MIN };
	OutExpr(thirdMax(nums), "%d");
}
