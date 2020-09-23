#include "leetcode.hpp"

/* 1458. 两个子序列的最大点积

给你两个数组 nums1 和 nums2 。

请你返回 nums1 和 nums2 中两个长度相同的 非空 子序列的最大点积。

数组的非空子序列是通过删除原数组中某些元素（可能一个也不删除）后剩余数字组成的序列，但不能改变数字间相对顺序。
比方说，[2,3,5] 是 [1,2,3,4,5] 的一个子序列而 [1,5,3] 不是。

示例 1：
输入：nums1 = [2,1,-2,5], nums2 = [3,0,-6]
输出：18
解释：从 nums1 中得到子序列 [2,-2] ，从 nums2 中得到子序列 [3,-6] 。
它们的点积为 (2*3 + (-2)*(-6)) = 18 。

示例 2：
输入：nums1 = [3,-2], nums2 = [2,-6,7]
输出：21
解释：从 nums1 中得到子序列 [3] ，从 nums2 中得到子序列 [7] 。
它们的点积为 (3*7) = 21 。

示例 3：
输入：nums1 = [-1,-1], nums2 = [1,1]
输出：-1
解释：从 nums1 中得到子序列 [-1] ，从 nums2 中得到子序列 [1] 。
它们的点积为 -1 。

提示：
	1 <= nums1.length, nums2.length <= 500
	-1000 <= nums1[i], nums2[i] <= 100
*/

int maxDotProduct1(vector<int>& A, vector<int>& B)
{
	int alen = static_cast<int>(A.size());
	int blen = static_cast<int>(B.size());
	int ans = INT_MIN;
	vector<int> up(blen + 1), dp(blen + 1);
	for (int a = 0; a < alen; ++a)
	{
		int cur = 0;
		for (int b = 0; b < blen; ++b)
		{
			int val = A[a] * B[b];
			cur = max(cur, up[b]);
			dp[b + 1] = val + cur;
		}
		for (int b = 1; b <= blen; ++b)
		{
			ans = max(ans, dp[b]);
			up[b] = max(up[b], dp[b]);
		}
	}
	return ans;
}


// https://leetcode.com/problems/max-dot-product-of-two-subsequences/discuss/648420/JavaC%2B%2BPython-the-Longest-Common-Sequence
// 抄的
int maxDotProduct(vector<int>& A, vector<int>& B)
{
	int alen = static_cast<int>(A.size());
	int blen = static_cast<int>(B.size());
	vector<int> pre(blen), cur(blen);
	for (int a = 0; a < alen; ++a)
	{
		pre.swap(cur);
		for (int b = 0; b < blen; ++b)
		{
			cur[b] = A[a] * B[b];
			// 这里必须先左上角判断以防用新的值
			if (a > 0 && b > 0)
				cur[b] = max(cur[b], cur[b] + pre[b - 1]);
			if (a > 0)
				cur[b] = max(cur[b], pre[b]);
			if (b > 0)
				cur[b] = max(cur[b], cur[b - 1]);
		}
	}
	return cur[blen - 1];
}

int main()
{
	vector<int>
		a = { 2, 1, -2, 5 },
		b = { 3, 0, -6 },
		c = { 3, -2 },
		d = { 2, -6, 7 },
		e = { -1, -1 },
		f = { 1, 1 },
		g = { 7, 2, 2, -1, -1, 1, -4, 7, 6 },
		h = { -7, -9, -1, 2, 2, 5, -7, 2, -7, 5 };
	OutExpr(maxDotProduct(a, b), "%d");
	OutExpr(maxDotProduct(c, d), "%d");
	OutExpr(maxDotProduct(e, f), "%d");
	OutExpr(maxDotProduct(g, h), "%d");
}
