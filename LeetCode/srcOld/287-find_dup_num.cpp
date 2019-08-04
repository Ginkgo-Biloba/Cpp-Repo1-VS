#include "leetcode.hpp"


// https://leetcode.com/problems/find-the-duplicate-number/discuss/72872/O(32*N)-solution-using-bit-manipulation-in-10-lines
// 抄的
int findDuplicate(vector<int> nums)
{
	int const len = static_cast<int>(nums.size());
	int const bits = sizeof(int) * 8;
	int p[bits] = { 0 }, q[bits] = { 0 };

	for (int i = 0; i < len; ++i)
	{
		int val = nums[i];
		// leetcdoe 未定义行为都报错
		// 这里会出现负数移位和有符号数溢出
		unsigned mask = 1; 

		for (int b = 0; b < bits; ++b)
		{
			if (val & mask) ++p[b];
			if (i & mask) ++q[b]; // 反正 0 也加不上去
			mask <<= 1;
		}
	}

	int ans = 0;
	for (int b = 0; b < bits; ++b)
	{
		if (p[b] > q[b]) // 至少出现 2 次，所以会有大于关系
			ans |= (1 << b);
	}
	return ans;
}


int main()
{
	vector<int> nums = { 1, 2, 4, 2, 2 };
	int n = findDuplicate(nums);
	printf("findDuplicate: %d\n", n);
}
