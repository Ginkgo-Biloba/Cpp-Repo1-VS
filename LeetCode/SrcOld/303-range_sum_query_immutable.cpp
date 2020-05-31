#include "leetcode.hpp"

/* 303. 区域和检索 - 数组不可变

给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。

示例：

给定 nums = [-2, 0, 3, -5, 2, -1]，求和函数为 sumRange()

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

说明:
	你可以假设数组不可变。
	会多次调用 sumRange 方法。
*/

class NumArray
{
	vector<int> p;

public:
	NumArray(vector<int>& nums)
	{
		size_t len = nums.size();
		p.resize(len + 1);
		for (size_t i = 0; i < len; ++i)
			p[i + 1] = p[i] + nums[i];
	}

	int sumRange(int i, int j)
	{
		return p[j + 1] - p[i];
	}
};


int main()
{}
