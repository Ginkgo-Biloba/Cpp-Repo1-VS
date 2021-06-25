#include "leetcode.hpp"

/* 1775. 通过最少操作次数使数组的和相等

给你两个长度可能不等的整数数组 nums1 和 nums2 。
两个数组中的所有值都在 1 到 6 之间（包含 1 和 6）。

每次操作中，你可以选择 任意 数组中的任意一个整数，将它变成 1 到 6 之间 任意 的值（包含 1 和 6）。

请你返回使 nums1 中所有数的和与 nums2 中所有数的和相等的最少操作次数。
如果无法使两个数组的和相等，请返回 -1 。

示例 1：
输入：nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
输出：3
解释：你可以通过 3 次操作使 nums1 中所有数的和与 nums2 中所有数的和相等。
以下数组下标都从 0 开始。
- 将 nums2[0] 变为 6 。 nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2] 。
- 将 nums1[5] 变为 1 。 nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2] 。
- 将 nums1[2] 变为 2 。 nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2] 。

示例 2：
输入：nums1 = [1,1,1,1,1,1,1], nums2 = [6]
输出：-1
解释：没有办法减少 nums1 的和或者增加 nums2 的和使二者相等。

示例 3：
输入：nums1 = [6,6], nums2 = [1]
输出：3
解释：你可以通过 3 次操作使 nums1 中所有数的和与 nums2 中所有数的和相等。
以下数组下标都从 0 开始。
- 将 nums1[0] 变为 2 。 nums1 = [2,6], nums2 = [1] 。
- 将 nums1[1] 变为 2 。 nums1 = [2,2], nums2 = [1] 。
- 将 nums2[0] 变为 4 。 nums1 = [2,2], nums2 = [4] 。

提示：
	1 <= nums1.length, nums2.length <= 10^5
	1 <= nums1[i], nums2[i] <= 6
*/

// https://leetcode-cn.com/problems/equal-sum-arrays-with-minimum-number-of-operations/solution/tong-guo-zui-shao-cao-zuo-ci-shu-shi-shu-o8no/
// 抄的
int minOperations(vector<int>& A, vector<int>& B)
{
	int a = 0, b = 0;
	for (int i : A)
		a += i;
	for (int i : B)
		b += i;
	if (a > b)
	{
		std::swap(a, b);
		A.swap(B);
	}
	int diff = b - a;
	int freq[6] = { 0 };
	for (int i : A)
		++freq[6 - i];
	for (int i : B)
		++freq[i - 1];
	int ans = 0;
	for (int i = 5; i > 0 && diff > 0; --i)
		if (freq[i])
		{
			int can = min(freq[i], (diff + i - 1) / i);
			ans += can;
			diff -= can * i;
		}
	return diff > 0 ? -1 : ans;
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 4, 5, 6 },
		b = { 1, 1, 2, 2, 2, 2 },
		c = { 1, 1, 1, 1, 1, 1, 1 },
		d = { 6 },
		e = { 6, 6 },
		f = { 1 };
	OutExpr(minOperations(a, b), "%d");
	OutExpr(minOperations(c, d), "%d");
	OutExpr(minOperations(e, f), "%d");
}
