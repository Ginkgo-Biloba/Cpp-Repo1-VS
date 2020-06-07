#include "leetcode.hpp"

/* 327. 区间和的个数

给定一个整数数组 nums，返回区间和在 [lower, upper] 之间的个数，包含 lower 和 upper。
区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)。

说明:
最直观的算法复杂度是 O(n2) ，请在此基础上优化你的算法。

示例:
输入: nums = [-2,5,-1], lower = -2, upper = 2,
输出: 3
解释: 3个区间分别是: [0,0], [2,2], [0,2]，它们表示的和分别为: -2, -1, 2。
*/

// https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/138154/The-C%2B%2B-merge-sort-template-for-pairs-'i'-'j'-problem
// 抄的
class Solution
{
	vector<int64_t> A, B;
	int64_t lo, hi;
	int ans;

	void merge(int h, int i, int k)
	{
		int b = h, p = h, q = i;
		for (; p < i && q < k; ++b)
		{
			if (A[p] < A[q])
			{
				B[b] = A[p];
				++p;
			}
			else
			{
				B[b] = A[q];
				++q;
			}
		}
		for (; p < i; ++p, ++b)
			B[b] = A[p];
		for (; q < k; ++q, ++b)
			B[b] = A[q];
		for (b = h; b < k; ++b)
			A[b] = B[b];
	}

	// 左闭右开区间 [left, right)
	void sort(int left, int right)
	{
		if (left + 1 >= right)
			return;

		int mid = (left + right) / 2;
		sort(left, mid);
		sort(mid, right);

		int L = left, M = mid, R = mid;
		for (; L < mid; ++L)
		{
			while ((M < right)
				&& (A[M] - A[L] < lo))
				++M;
			while ((R < right)
				&& (A[R] - A[L] <= hi))
				++R;
			ans += R - M;
		}
		merge(left, mid, right);
	}


public:
	int countRangeSum(vector<int>& nums, int lower, int upper)
	{
		lo = lower;
		hi = upper;
		int len = static_cast<int>(nums.size());
		A.assign(len + 1, 0);
		B.resize(len + 1);
		for (int i = 0; i < len; ++i)
			A[i + 1] = A[i] + nums[i];

		ans = 0;
		sort(0, len + 1);
		return ans;
	}
};


int main()
{
	vector<int> a = { -2, 5, -1 };
	Solution s;
	OutExpr(s.countRangeSum(a, -2, 2), "%d");
}
