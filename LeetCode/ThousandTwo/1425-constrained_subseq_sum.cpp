#include "leetcode.hpp"

/* 1425. 带限制的子序列和

给你一个整数数组 nums 和一个整数 k ，请你返回 非空 子序列元素和的最大值，子序列需要满足：子序列中每两个 相邻 的整数 nums[i] 和 nums[j] ，它们在原数组中的下标 i 和 j 满足 i < j 且 j - i <= k 。

数组的子序列定义为：将数组中的若干个数字删除（可以删除 0 个数字），剩下的数字按照原本的顺序排布。

示例 1：
输入：nums = [10,2,-10,5,20], k = 2
输出：37
解释：子序列为 [10, 2, 5, 20] 。

示例 2：
输入：nums = [-1,-2,-3], k = 1
输出：-1
解释：子序列必须是非空的，所以我们选择最大的数字。

示例 3：
输入：nums = [10,-2,-10,-5,20], k = 2
输出：23
解释：子序列为 [10, -2, -5, 20] 。

提示：
	1 <= k <= nums.length <= 10^5
	-10^4 <= nums[i] <= 10^4
*/

// https://leetcode.com/problems/constrained-subsequence-sum/discuss/597751/JavaC%2B%2BPython-O(N)-Decreasing-Deque
// 抄的
int constrainedSubsetSum0(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	deque<int> Q;
	int ans = A[0];
	for (int i = 0; i < len; ++i)
	{
		if (Q.size())
			A[i] += Q.front();
		ans = max(ans, A[i]);
		while (Q.size() && Q.back() < A[i])
			Q.pop_back();
		if (A[i] > 0)
			Q.push_back(A[i]);
		if (i >= k && Q.size() && Q.front() == A[i - k])
			Q.pop_front();
	}
	return ans;
}

int constrainedSubsetSum(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	priority_queue<pair<int, int>> Q;
	int cur, ans = A[0];
	for (int i = 0; i < len; ++i)
	{
		cur = A[i];
		if (Q.size())
			cur += Q.top().first;
		ans = max(ans, cur);
		while (Q.size() && Q.top().first < A[i])
			Q.pop();
		if (cur > 0)
			Q.emplace(cur, i);
		if (Q.size() && Q.top().second <= i - k)
			Q.pop();
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 10, 2, -10, 5, 20 },
		b = { -1, -2, -3 },
		c = { 10, -2, -10, -5, 20 };
	OutExpr(constrainedSubsetSum(a, 2), "%d");
	OutExpr(constrainedSubsetSum(b, 1), "%d");
	OutExpr(constrainedSubsetSum(c, 2), "%d");
}
