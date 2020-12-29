#include "leetcode.hpp"

/* 1673. 找出最具竞争力的子序列

给你一个整数数组 nums 和一个正整数 k ，返回长度为 k 且最具 竞争力 的 nums 子序列。

数组的子序列是从数组中删除一些元素（可能不删除元素）得到的序列。

在子序列 a 和子序列 b 第一个不相同的位置上，如果 a 中的数字小于 b 中对应的数字，那么我们称子序列 a 比子序列 b（相同长度下）更具 竞争力 。
例如，[1,3,4] 比 [1,3,5] 更具竞争力，在第一个不相同的位置，也就是最后一个位置上， 4 小于 5 。

示例 1：
输入：nums = [3,5,2,6], k = 2
输出：[2,6]
解释：在所有可能的子序列集合 {[3,5], [3,2], [3,6], [5,2], [5,6], [2,6]} 中，[2,6] 最具竞争力。

示例 2：
输入：nums = [2,4,3,3,5,4,9,6], k = 4
输出：[2,3,3,4]

提示：
	1 <= nums.length <= 10^5
	0 <= nums[i] <= 10^9
	1 <= k <= nums.length
*/

vector<int> mostCompetitive1(vector<int>& nums, int k)
{
	vector<int> A;
	priority_queue<pair<int, int>> Q;
	int n = static_cast<int>(nums.size());
	int m = n - k;
	for (int i = 0; i < m; ++i)
		Q.push({ -nums[i], -i });
	k = 0;
	for (int i = m; i < n; ++i)
	{
		Q.push({ -nums[i], -i });
		k = min(k, m - i);
		while (Q.top().second > k)
			Q.pop();
		A.push_back(-(Q.top().first));
		k = min(k, Q.top().second);
		Q.pop();
	}
	return A;
}

// https://leetcode.com/problems/find-the-most-competitive-subsequence/discuss/952786/JavaC%2B%2BPython-One-Pass-Stack-Solution
// 抄的
vector<int> mostCompetitive(vector<int>& A, int k)
{
	int n = static_cast<int>(A.size());
	vector<int> S(k);
	int j = 0;
	for (int i = 0; i < n; ++i)
	{
		while (j && S[j - 1] > A[i] && j - 1 + n - i >= k)
			j--;
		if (j < k)
			S[j++] = A[i];
	}
	return S;
}


int main()
{}
