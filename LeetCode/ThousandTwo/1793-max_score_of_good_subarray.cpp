#include "leetcode.hpp"

/* 1793. 好子数组的最大分数

给你一个整数数组 nums （下标从 0 开始）和一个整数 k 。

一个子数组 (i, j) 的 分数 定义为 min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1) 。
一个 好 子数组的两个端点下标需要满足 i <= k <= j 。

请你返回 好 子数组的最大可能 分数 。

示例 1：

输入：nums = [1,4,3,7,4,5], k = 3
输出：15
解释：最优子数组的左右端点下标是 (1, 5) ，分数为 min(4,3,7,4,5) * (5-1+1) = 3 * 5 = 15 。

示例 2：

输入：nums = [5,5,4,5,4,1,1,1], k = 0
输出：20
解释：最优子数组的左右端点下标是 (0, 4) ，分数为 min(5,5,4,5,4) * (4-0+1) = 4 * 5 = 20 。

提示：
	1 <= nums.length <= 10^5
	1 <= nums[i] <= 2 * 10^4
	0 <= k < nums.length。
*/

// https://leetcode.com/problems/maximum-score-of-a-good-subarray/discuss/1108333/JavaC%2B%2BPython-Two-Pointers
// 抄的
int maximumScore(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	int ans = A[k], lo = A[k];
	int i = k, j = k;
	while (i > 1 || j < len - 1)
	{
		if (i == 0)
			++j;
		else if (j == len - 1)
			--i;
		else if (A[i - 1] < A[j + 1])
			++j;
		else
			--i;
		lo = min(lo, min(A[i], A[j]));
		ans = max(ans, lo * (j - i + 1));
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 1, 4, 3, 7, 4, 5 },
		b = { 5, 5, 4, 5, 4, 1, 1, 1 };
	OutExpr(maximumScore(a, 3), "%d");
	OutExpr(maximumScore(b, 0), "%d");
}
