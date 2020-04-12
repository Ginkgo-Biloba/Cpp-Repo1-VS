#include "leetcode.hpp"

/* 1250. 检查「好数组」

给你一个正整数数组 nums，你需要从中任选一些子集，然后将子集中每一个数乘以一个 任意整数，并求出他们的和。

假如该和结果为 1，那么原数组就是一个「好数组」，则返回 True；否则请返回 False。

示例 1：
输入：nums = [12,5,7,23]
输出：true
解释：挑选数字 5 和 7。
5*3 + 7*(-2) = 1

示例 2：
输入：nums = [29,6,10]
输出：true
解释：挑选数字 29, 6 和 10。
29*1 + 6*(-3) + 10*(-1) = 1

示例 3：
输入：nums = [3,6]
输出：false

提示：
	1 <= nums.length <= 10^5
	1 <= nums[i] <= 10^9
*/

int gcd(int a, int b)
{
	assert(b != 0);
	int t = a % b;
	while (t)
	{
		a = b;
		b = t;
		t = a % b;
	}
	return b;
}

bool isGoodArray(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	int t = nums[0];
	for (int i = 1; i < len; ++i)
	{
		t = gcd(t, nums[i]);
		if (t == 1)
			break;
	}
	return t == 1;
}


int main()
{}
