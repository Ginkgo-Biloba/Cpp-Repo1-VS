#include "leetcode.hpp"

/* 137. 只出现一次的数字 II

给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。
找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。
你可以不使用额外空间来实现吗？

示例 1:
输入: [2,2,3,2]
输出: 3

示例 2:
输入: [0,1,0,1,0,1,99]
输出: 99
*/

int singleNumber_Org(vector<int>& nums)
{
	unsigned cnt[32] = { 0 };
	for (int n : nums)
		for (int b = 0; b < 32; ++b)
			cnt[b] += !!(n & (1U << b));
	int ans = 0;
	for (int b = 0; b < 32; ++b)
		ans |= (cnt[b] % 3) << b;
	return ans;
}

// https://leetcode.com/problems/single-number-ii/discuss/43295/Detailed-explanation-and-generalization-of-the-bitwise-operation-method-for-single-numbers
int singleNumber2(vector<int>& nums)
{
	int x2 = 0, x1 = 0, mask = 0;
	for (int n : nums)
	{
		x2 ^= x1 & n;
		x1 ^= n;
		mask = ~(x1 & x2);
		x2 &= mask;
		x1 &= mask;
	}
	return x1;
}


// https://leetcode-cn.com/problems/single-number-ii/solution/luo-ji-dian-lu-jiao-du-xiang-xi-fen-xi-gai-ti-si-l/
// 抄的
int singleNumber(vector<int>& nums)
{
	int a = 0, b = 0;
	for (int n : nums)
	{
		b = (b ^ n) & (~a);
		a = (a ^ n) & (~b);
	}
	return b;
}

int main()
{
	vector<int>
		a = { 2, 2, 3, 2 },
		b = { 0, 1, 0, 1, 0, 1, 99 };
	OutExpr(singleNumber_Org(a), "%d");
	OutExpr(singleNumber_Org(b), "%d");
}
