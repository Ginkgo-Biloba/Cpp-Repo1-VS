#include "leetcode.hpp"

/* 421. 数组中两个数的最大异或值

给定一个非空数组，数组中元素为 a0, a1, a2, … , an-1，其中 0 ≤ ai < 231 。
找到 ai 和aj 最大的异或 (XOR) 运算结果，其中0 ≤ i,  j < n 。
你能在O(n)的时间解决这个问题吗？

示例:
输入: [3, 10, 5, 25, 2, 8]
输出: 28
解释: 最大的结果是 5 ^ 25 = 28.
*/

// https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/91049/Java-O(n)-solution-using-bit-manipulation-and-HashMap
// 抄的
int findMaximumXOR(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	int ans = 0, mask = 0;
	for (int i = 31; i >= 0; --i)
	{
		mask |= (1U << i);
		unordered_set<int> us;
		for (int n = 0; n < len; ++n)
			us.insert(nums[n] & mask);
		int t = ans | (1U << i);
		for (int prefix : us)
			if (us.find(t ^ prefix) != us.end())
			{
				ans = t;
				break;
			}
	}
	return ans;
}


int main()
{
	vector<int> nums = { 3, 10, 5, 25, 2, 8 };
	OutExpr(findMaximumXOR(nums), "%d");
}
