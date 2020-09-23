#include "leetcode.hpp"

/* 1493. 删掉一个元素以后全为 1 的最长子数组

给你一个二进制数组 nums ，你需要从中删掉一个元素。

请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。

如果不存在这样的子数组，请返回 0 。

提示 1：
输入：nums = [1,1,0,1]
输出：3
解释：删掉位置 2 的数后，[1,1,1] 包含 3 个 1 。

示例 2：
输入：nums = [0,1,1,1,0,1,1,0,1]
输出：5
解释：删掉位置 4 的数字后，[0,1,1,1,1,1,0,1] 的最长全 1 子数组为 [1,1,1,1,1] 。

示例 3：
输入：nums = [1,1,1]
输出：2
解释：你必须要删除一个元素。

示例 4：
输入：nums = [1,1,0,0,1,1,1,0,1]
输出：4

示例 5：
输入：nums = [0,0,0]
输出：0

提示：
	1 <= nums.length <= 10^5
	nums[i] 要么是 0 要么是 1 。
*/

int longestSubarray1(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int pre = 0, cur, ans = 0;
	int i = 0, k;
	for (; i < len; i = k)
	{
		k = i + 1;
		if (A[i])
		{
			++pre;
			continue;
		}
		if (k < len && A[k])
		{
			while (k < len && A[k])
				++k;
			cur = k - i - 1;
			ans = max(ans, pre + cur);
			pre = cur;
		}
		else
		{
			ans = max(ans, pre);
			while (k < len && A[k] == 0)
				++k;
			pre = 0;
		}
	}
	ans = max(ans, pre);
	ans = min(ans, len - 1);
	return ans;
}

// https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/discuss/708112/JavaC%2B%2BPython-Sliding-Window-at-most-one-0
// 人家的优雅写法
int longestSubarray(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int i = 0, k = 0, m = 1;
	for (; k < len; ++k)
	{
		m -= (A[k] == 0);
		if (m < 0)
			m += A[i++] == 0;
	}
	return k - i - 1;
}


int main()
{
	vector<int>
		a = { 1, 1, 0, 1 },
		b = { 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		c = { 1, 1, 1 },
		d = { 1, 1, 0, 0, 1, 1, 1, 0, 1 },
		e = { 0, 0, 0 };
	OutExpr(longestSubarray(a), "%d");
	OutExpr(longestSubarray(b), "%d");
	OutExpr(longestSubarray(c), "%d");
	OutExpr(longestSubarray(d), "%d");
	OutExpr(longestSubarray(e), "%d");
}
