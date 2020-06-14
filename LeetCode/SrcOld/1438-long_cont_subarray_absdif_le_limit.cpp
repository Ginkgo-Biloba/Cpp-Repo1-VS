#include "leetcode.hpp"

/* 1438. 绝对差不超过限制的最长连续子数组

给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。

如果不存在满足条件的子数组，则返回 0 。

示例 1：

输入：nums = [8,2,4,7], limit = 4
输出：2
解释：所有子数组如下：
[8] 最大绝对差 |8-8| = 0 <= 4.
[8,2] 最大绝对差 |8-2| = 6 > 4.
[8,2,4] 最大绝对差 |8-2| = 6 > 4.
[8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
[2] 最大绝对差 |2-2| = 0 <= 4.
[2,4] 最大绝对差 |2-4| = 2 <= 4.
[2,4,7] 最大绝对差 |2-7| = 5 > 4.
[4] 最大绝对差 |4-4| = 0 <= 4.
[4,7] 最大绝对差 |4-7| = 3 <= 4.
[7] 最大绝对差 |7-7| = 0 <= 4.
因此，满足题意的最长子数组的长度为 2 。

示例 2：
输入：nums = [10,1,2,4,7,2], limit = 5
输出：4
解释：满足题意的最长子数组是 [2,4,7,2]，其最大绝对差 |2-7| = 5 <= 5 。

示例 3：
输入：nums = [4,2,2,2,4,4,2,2], limit = 0
输出：3

提示：
	1 <= nums.length <= 10^5
	1 <= nums[i] <= 10^9
	0 <= limit <= 10^9
*/

// https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/solution/longest-continuous-subarray-by-ikaruga/
// 抄的
int longestSubarray1(vector<int>& A, int limit)
{
	int len = static_cast<int>(A.size());
	int h = 0, i = 0, ans = 0;
	map<int, int> M;
	for (; i < len; ++i)
	{
		M[A[i]] += 1;
		while (M.rbegin()->first - M.begin()->first > limit)
		{
			if (--(M[A[h]]) == 0)
				M.erase(A[h]);
			++h;
		}
		ans = max(ans, i - h + 1);
	}
	return ans;
}

int longestSubarray2(vector<int>& A, int limit)
{
	int len = static_cast<int>(A.size());
	int h = 0, i = 0;
	map<int, int> M;
	for (; i < len; ++i)
	{
		M[A[i]] += 1;
		if (M.rbegin()->first - M.begin()->first > limit)
		{
			if (--(M[A[h]]) == 0)
				M.erase(A[h]);
			++h;
		}
	}
	return i - h;
}


// https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/discuss/609771/JavaC%2B%2BPython-Deques-O(N)
// 抄的
int longestSubarray3(vector<int>& A, int limit)
{
	int len = static_cast<int>(A.size());
	int h = 0, i = 0, ans = 0;
	priority_queue<pair<int, int>> X, N;
	for (; i < len; ++i)
	{
		// 相同的数字保持小的索引在前面
		X.push({ +A[i], -i });
		N.push({ -A[i], -i });
		while (X.top().first + N.top().first > limit)
		{
			h = min(-(X.top().second), -(N.top().second)) + 1;
			while (-(X.top().second) < h)
				X.pop();
			while (-(N.top().second) < h)
				N.pop();
		}
		ans = max(ans, i - h + 1);
	}
	return ans;
}

int longestSubarray(vector<int>& A, int limit)
{
	int len = static_cast<int>(A.size());
	deque<int> X, N;
	int h = 0, i = 0;
	for (; i < len; ++i)
	{
		while (X.size() && A[i] > X.back())
			X.pop_back();
		while (N.size() && A[i] < N.back())
			N.pop_back();
		X.push_back(A[i]);
		N.push_back(A[i]);
		if (X.front() - N.front() > limit)
		{
			if (X.front() == A[h])
				X.pop_front();
			if (N.front() == A[h])
				N.pop_front();
			++h;
		}
	}
	return i - h;
}


int main()
{
	vector<int>
		a = { 8, 2, 4, 7 },
		b = { 10, 1, 2, 4, 7, 2 },
		c = { 4, 2, 2, 2, 4, 4, 2, 2 };
	OutExpr(longestSubarray(a, 4), "%d");
	OutExpr(longestSubarray(b, 5), "%d");
	OutExpr(longestSubarray(c, 0), "%d");
}
