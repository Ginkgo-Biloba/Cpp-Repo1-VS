#include "leetcode.hpp"

/* 1508. 子数组和排序后的区间和

给你一个数组 nums ，它包含 n 个正整数。
你需要计算所有非空连续子数组的和，并将它们按升序排序，得到一个新的包含 n * (n + 1) / 2 个数字的数组。

请你返回在新数组中下标为 left 到 right （下标从 1 开始）的所有数字和（包括左右端点）。
由于答案可能很大，请你将它对 10^9 + 7 取模后返回。

示例 1：
输入：nums = [1,2,3,4], n = 4, left = 1, right = 5
输出：13
解释：
所有的子数组和为 1, 3, 6, 10, 2, 5, 9, 3, 7, 4 。
将它们升序排序后，我们得到新的数组 [1, 2, 3, 3, 4, 5, 6, 7, 9, 10] 。
下标从 le = 1 到 ri = 5 的和为 1 + 2 + 3 + 3 + 4 = 13 。

示例 2：
输入：nums = [1,2,3,4], n = 4, left = 3, right = 4
输出：6
解释：
给定数组与示例 1 一样，所以新数组为 [1, 2, 3, 3, 4, 5, 6, 7, 9, 10] 。
下标从 le = 3 到 ri = 4 的和为 3 + 3 = 6 。

示例 3：
输入：nums = [1,2,3,4], n = 4, left = 1, right = 10
输出：50

提示：
	1 <= nums.length <= 10^3
	nums.length == n
	1 <= nums[i] <= 100
	1 <= left <= right <= n * (n + 1) / 2
*/

// https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/discuss/733047/Python-Binary-Search-Time-O(NlogSum(A))
// 抄的
class Solution
{
	vector<int> B, C;
	int n, mod;

	int cntLess(int val)
	{
		int m = 0, i = 0, k = 0;
		for (; k <= n; ++k)
		{
			while (B[k] - B[i] > val)
				++i;
			m += k - i;
		}
		return m;
	}

	int kth(int k)
	{
		int a = 0, b = B[n];
		while (a < b)
		{
			int m = (a + b) / 2;
			if (cntLess(m) < k)
				a = m + 1;
			else
				b = m;
		}
		return a;
	}

	int sumLess(int val)
	{
		int m = kth(val);
		int s = 0, i = 0, k = 0;
		for (; k <= n; ++k)
		{
			while (B[k] - B[i] > m)
				++i;
			s += B[k] * (k - i + 1);
			s %= mod;
			if (i)
				s -= C[k] - C[i - 1];
			else
				s -= C[k];
			s %= mod;
		}
		s -= (cntLess(m) - val) * m;
		return s % mod;
	}

public:
	int rangeSum(vector<int>& A, int, int left, int right)
	{
		mod = 1e9 + 7;
		n = static_cast<int>(A.size());
		B.assign(n + 1, 0);
		C.assign(n + 1, 0);
		for (int i = 0; i < n; ++i)
		{
			B[i + 1] = B[i] + A[i];
			C[i + 1] = C[i] + B[i + 1];
		}
		int p = sumLess(left - 1);
		int q = sumLess(right);
		return (q - p + mod) % mod;
	}
};


int main()
{
	Solution s;
	vector<int> a = { 1, 2, 3, 4 };
	OutExpr(s.rangeSum(a, -1, 1, 5), "%d");
	OutExpr(s.rangeSum(a, -1, 3, 4), "%d");
	OutExpr(s.rangeSum(a, -1, 1, 10), "%d");
}
