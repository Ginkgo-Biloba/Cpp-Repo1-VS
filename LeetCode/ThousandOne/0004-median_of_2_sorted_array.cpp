#include "leetcode.hpp"

/* 4. 寻找两个有序数组的中位数

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0

示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5
*/

// https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2481/Share-my-O(log(min(mn)))-solution-with-explanation
// 抄的
double findMedianSortedArrays(vector<int>& A, vector<int>& B)
{
	if (A.size() > B.size())
		A.swap(B);
	int m = static_cast<int>(A.size());
	int n = static_cast<int>(B.size());
	int half = (m + n + 1) / 2;
	int imin = 0, imax = m;
	while (imin <= imax)
	{
		int i = (imin + imax) / 2;
		int j = half - i;
		if (i < m && B[j - 1] > A[i])
			imin = i + 1;
		else if (i > 0 && A[i - 1] > B[j])
			imax = i - 1;
		else
		{
			int lmax = INT_MIN, rmin = INT_MAX;
			if (i > 0)
				lmax = max(lmax, A[i - 1]);
			if (j > 0)
				lmax = max(lmax, B[j - 1]);
			if ((m + n) % 2)
				return lmax;
			if (i < m)
				rmin = min(rmin, A[i]);
			if (j < n)
				rmin = min(rmin, B[j]);
			return (lmax + rmin) / 2.0;
		}
	}
	return -1.0;
}

int main()
{
	vector<int>
		a = { 1, 3 },
		b = { 2 },
		c = { 1, 2 },
		d = { 3, 4 };
	OutExpr(findMedianSortedArrays(a, b), "%f");
	OutExpr(findMedianSortedArrays(c, d), "%f");
}
