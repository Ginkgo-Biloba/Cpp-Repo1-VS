#include "leetcode.hpp"

/* 1537. 最大得分

你有两个 有序 且数组内元素互不相同的数组 nums1 和 nums2 。

一条 合法路径 定义如下：

选择数组 nums1 或者 nums2 开始遍历（从下标 0 处开始）。
从左到右遍历当前数组。
如果你遇到了 nums1 和 nums2 中都存在的值，那么你可以切换路径到另一个数组对应数字处继续遍历（但在合法路径中重复数字只会被统计一次）。

得分定义为合法路径中不同数字的和。

请你返回所有可能合法路径中的最大得分。

由于答案可能很大，请你将它对 10^9 + 7 取余后返回。


示例 1：
https://assets.leetcode.com/uploads/2020/07/16/sample_1_1893.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/02/sample_1_1893.png
输入：nums1 = [2,4,5,8,10], nums2 = [4,6,8,9]
输出：30
解释：合法路径包括：
[2,4,5,8,10], [2,4,5,8,9], [2,4,6,8,9], [2,4,6,8,10],（从 nums1 开始遍历）
[4,6,8,9], [4,5,8,10], [4,5,8,9], [4,6,8,10]  （从 nums2 开始遍历）
最大得分为上图中的绿色路径 [2,4,6,8,10] 。

示例 2：
输入：nums1 = [1,3,5,7,9], nums2 = [3,5,100]
输出：109
解释：最大得分由路径 [1,3,5,100] 得到。

示例 3：
输入：nums1 = [1,2,3,4,5], nums2 = [6,7,8,9,10]
输出：40
解释：nums1 和 nums2 之间无相同数字。
最大得分由路径 [6,7,8,9,10] 得到。

示例 4：
输入：nums1 = [1,4,5,8,9,11,19], nums2 = [2,3,4,11,12]
输出：61

提示：
	1 <= nums1.length <= 10^5
	1 <= nums2.length <= 10^5
	1 <= nums1[i], nums2[i] <= 10^7
	nums1 和 nums2 都是严格递增的数组。
*/

// 赛后抄的第一名的，第一名改版。。。
int maxSum0(vector<int>& nums1, vector<int>& nums2)
{
	int64_t const mod = 1e9 + 7;
	int64_t a = 0, b = 0;
	map<int, int> M;
	for (int i : nums1) M[i] += 1;
	for (int i : nums2) M[i] += 2;
	for (auto const& kv : M)
	{
		if (kv.second == 1) a += kv.first;
		if (kv.second == 2) b += kv.first;
		if (kv.second == 3) a = b = max(a, b) + kv.first;
	}
	return static_cast<int>(max(a, b) % mod);
}

// https://leetcode.com/problems/get-the-maximum-score/discuss/767987/JavaC++Python-Two-Pointers-O(1)-Space/639229
// 抄的
int maxSum(vector<int>& A, vector<int>& B)
{
	int64_t const mod = 1e9 + 7;
	int64_t a = 0, b = 0;
	int p = 0, q = 0;
	int m = static_cast<int>(A.size());
	int n = static_cast<int>(B.size());
	while (p < m && q < n)
	{
		if (A[p] < B[q])
		{
			a += A[p];
			++p;
		}
		else if (A[p] > B[q])
		{
			b += B[q];
			++q;
		}
		else
		{
			a = b = max(a, b) + A[p];
			++p;
			++q;
		}
	}
	for (; p < m; ++p) a += A[p];
	for (; q < n; ++q) b += B[q];
	a = b = max(a, b) % mod;
	return static_cast<int>(a);
}


int main()
{
	vector<int>
		a = { 2, 4, 5, 8, 10 },
		b = { 4, 6, 8, 9 },
		c = { 1, 3, 5, 7, 9 },
		d = { 3, 5, 100 },
		e = { 1, 2, 3, 4, 5 },
		f = { 6, 7, 8, 9, 10 },
		g = { 1, 4, 5, 8, 9, 11, 19 },
		h = { 2, 3, 4, 11, 12 };
	OutExpr(maxSum(a, b), "%d");
	OutExpr(maxSum(c, d), "%d");
	OutExpr(maxSum(e, f), "%d");
	OutExpr(maxSum(g, h), "%d");
}
