#include "leetcode.hpp"

/* 307. 区域和检索 - 数组可修改

给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。

update(i, val) 函数可以通过将下标为 i 的数值更新为 val，从而对数列进行修改。

示例:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8

说明:
	数组仅可以在 update 函数下进行修改。
	你可以假设 update 函数与 sumRange 函数的调用次数是均匀分布的。
*/

// https://leetcode-cn.com/problems/range-sum-query-mutable/solution/cshu-zhuang-shu-zu-by-liyupi/
// 线段树。没写过，直接抄的
class NumArray
{
public:
	vector<int> C;
	vector<int>& nums;
	int size;
	NumArray(vector<int>& _nums)
		: nums(_nums)
	{
		size = static_cast<int>(nums.size());
		C.resize(size + 1);
		memset(C.data(), 0, (size + 1) * sizeof(int));
		for (int i = 0; i < size; ++i)
			add(i, nums[i]);
	}
	int lowbit(int x)
	{
		return x & (-x);
	}
	void add(int i, int val)
	{
		for (int k = i + 1; k <= size; k += lowbit(k))
			C[k] += val;
	}
	void update(int i, int val)
	{
		int delta = val - nums[i];
		nums[i] = val;
		for (int k = i + 1; k <= size; k += lowbit(k))
			C[k] += delta;
	}
	int getSum(int i)
	{
		int sum = 0;
		for (int k = i; k > 0; k -= lowbit(k))
			sum += C[k];
		return sum;
	}
	int sumRange(int i, int j)
	{
		return getSum(j + 1) - getSum(i);
	}
};


int main()
{
	vector<int> nums = { 1, 3, 5 };
	NumArray ary(nums);
	OutExpr(ary.sumRange(0, 2), "%d");
	ary.update(1, 2);
	OutExpr(ary.sumRange(0, 2), "%d");
}
