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

// https://leetcode.com/problems/range-sum-query-mutable/discuss/75721/strongly-recommend-for-beginnersclean-C%2B%2B-implementation-with-detailed-explaination
// 抄的
class NumArray
{
	vector<int> C, A;
	int size;

	int lowbit(int x)
	{
		return x & (-x);
	}

	void add(int i, int val)
	{
		for (int k = i + 1; k <= size; k += lowbit(k))
			C[k] += val;
	}

	int getSum(int i)
	{
		int sum = 0;
		for (int k = i; k > 0; k -= lowbit(k))
			sum += C[k];
		return sum;
	}

public:
	NumArray(vector<int>& nums)
	{
		A.swap(nums);
		size = static_cast<int>(A.size());
		C.resize(size + 1);
		memset(C.data(), 0, (size + 1) * sizeof(int));
		for (int i = 0; i < size; ++i)
			add(i, A[i]);
	}

	void update(int i, int val)
	{
		int delta = val - A[i];
		A[i] = val;
		for (int k = i + 1; k <= size; k += lowbit(k))
			C[k] += delta;
	}

	int sumRange(int i, int j)
	{
		return getSum(j + 1) - getSum(i);
	}
};


int main()
{
	vector<int> a = { 1, 3, 5 };
	NumArray n(a);
	OutExpr(n.sumRange(0, 2), "%d");
	n.update(1, 2);
	OutExpr(n.sumRange(0, 2), "%d");
}
