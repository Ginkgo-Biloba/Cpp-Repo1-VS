#include "leetcode.hpp"

/* 1340. 跳跃游戏 V

给你一个整数数组 arr 和一个整数 d 。每一步你可以从下标 i 跳到：
	i + x ，其中 i + x < arr.length 且 0 < x <= d 。
	i - x ，其中 i - x >= 0 且 0 < x <= d。

除此以外，你从下标 i 跳到下标 j 需要满足：arr[i] > arr[j] 且 arr[i] > arr[k]，其中下标 k 是所有 i 到 j 之间的数字（更正式的，min(i, j) < k < max(i, j)）。

你可以选择数组的任意下标开始跳跃。请你返回你 最多 可以访问多少个下标。

请注意，任何时刻你都不能跳到数组的外面。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/02/02/meta-chart.jpeg
输入：arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
输出：4
解释：你可以从下标 10 出发，然后如上图依次经过 10 --> 8 --> 6 --> 7 。
注意，如果你从下标 6 开始，你只能跳到下标 7 处。你不能跳到下标 5 处因为 13 > 9 。你也不能跳到下标 4 处，因为下标 5 在下标 4 和 6 之间且 13 > 9 。
类似的，你不能从下标 3 处跳到下标 2 或者下标 1 处。

示例 2：
输入：arr = [3,3,3,3,3], d = 3
输出：1
解释：你可以从任意下标处开始且你永远无法跳到任何其他坐标。

示例 3：
输入：arr = [7,6,5,4,3,2,1], d = 1
输出：7
解释：从下标 0 处开始，你可以按照数值从大到小，访问所有的下标。

示例 4：
输入：arr = [7,1,7,1,7,1], d = 2
输出：2

示例 5：
输入：arr = [66], d = 1
输出：1

提示：
	1 <= arr.length <= 1000
	1 <= arr[i] <= 10^5
	1 <= d <= arr.length
*/

int maxJumps_1(vector<int>& A, int d)
{
	int len = static_cast<int>(A.size());
	int cur;
	vector<int> jump(len, 1);
	vector<int> idxs;
	idxs.reserve(len);
	for (int i = 0; i < len; ++i)
		idxs.push_back(i);
	sort(idxs.begin(), idxs.end(),
		[&A](int a, int b) -> bool { return A[a] < A[b]; });
	for (int i : idxs)
	{
		cur = jump[i];
		for (int k = 1; k <= d; ++k)
		{
			if (i + k >= len || A[i] <= A[i + k])
				break;
			cur = max(cur, jump[i + k] + 1);
		}
		for (int k = 1; k <= d; ++k)
		{
			if (i - k < 0 || A[i] <= A[i - k])
				break;
			cur = max(cur, jump[i - k] + 1);
		}
		jump[i] = cur;
	}
	cur = 0;
	for (int i = 0; i < len; ++i)
		cur = max(cur, jump[i]);
	return cur;
}


// https://mp.weixin.qq.com/s/kEQ00_WLqDTG6tbsjQ2Xjw
// 抄的
int maxJumps(vector<int>& A, int d)
{
	int len = static_cast<int>(A.size());
	vector<int> dp(len + 1, 1);
	vector<int> s1, s2;
	A.push_back(INT_MAX);

	for (int i = 0; i <= len; ++i)
	{
		while (!s1.empty() && A[s1.back()] < A[i])
		{
			int pre = A[s1.back()];
			while (!s1.empty() && pre == A[s1.back()])
			{
				int k = s1.back();
				s1.pop_back();
				if (i - k <= d)
					dp[i] = max(dp[i], dp[k] + 1);
				s2.push_back(k);
			}
			while (!s2.empty())
			{
				int k = s2.back();
				s2.pop_back();
				if (!s1.empty() && k - s1.back() <= d)
					dp[s1.back()] = max(dp[s1.back()], dp[k] + 1);
			}
		}
		s1.push_back(i);
	}

	int cur = 0;
	for (int i = 0; i < len; ++i)
		cur = max(cur, dp[i]);
	return cur;
}


int main()
{
	vector<int>
		a = { 6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12 },
		b = { 3, 3, 3, 3, 3 },
		c = { 7, 6, 5, 4, 3, 2, 1 },
		d = { 7, 1, 7, 1, 7, 1 },
		e = { 66 };
	OutExpr(maxJumps(a, 2), "%d");
	OutExpr(maxJumps(b, 3), "%d");
	OutExpr(maxJumps(c, 1), "%d");
	OutExpr(maxJumps(d, 2), "%d");
	OutExpr(maxJumps(e, 1), "%d");
}
