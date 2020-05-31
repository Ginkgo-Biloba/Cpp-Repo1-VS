#include "leetcode.hpp"

/* 239. 滑动窗口最大值

给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的 k 个数字。
滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。

进阶：

你能在线性时间复杂度内解决此题吗？

示例:

输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7]
解释:

·   滑动窗口的位置                最大值
· ---------------               -----
· [1  3  -1] -3  5  3  6  7       3
·  1 [3  -1  -3] 5  3  6  7       3
·  1  3 [-1  -3  5] 3  6  7       5
·  1  3  -1 [-3  5  3] 6  7       5
·  1  3  -1  -3 [5  3  6] 7       6
·  1  3  -1  -3  5 [3  6  7]      7

提示：
	1 <= nums.length <= 10^5
	-10^4 <= nums[i] <= 10^4
	1 <= k <= nums.length
*/

vector<int> maxSlidingWindow_Org(vector<int>& nums, int k)
{
	int len = static_cast<int>(nums.size());
	vector<int> F = nums, B = nums, R(len - k + 1);
	int f = 0, b;
	for (int step = len / k; step > 0; --step)
	{
		b = f + k - 1;
		F[f] = nums[f];
		B[b] = nums[b];
		++f;
		--b;
		for (int s = k; --s; ++f, --b)
		{
			F[f] = max(F[f - 1], nums[f]);
			B[b] = max(B[b + 1], nums[b]);
		}
	}
	if (f < len)
	{
		b = len - 1;
		F[f] = nums[f];
		B[b] = nums[b];
		++f;
		--b;
		for (; f < len; ++f, --b)
		{
			F[f] = max(F[f - 1], nums[f]);
			B[b] = max(B[b + 1], nums[b]);
		}
	}

	f = 0;
	b = len - k + 1;
	for (; f < b; ++f)
		R[f] = max(F[f + k - 1], B[f]);
	return R;
}


vector<int> maxSlidingWindow(vector<int>& A, int k)
{
	if (k == 1)
		return A;
	int len = static_cast<int>(A.size());
	deque<int> Q;
	vector<int> R;
	for (int i = 0; i < k - 1; ++i)
	{
		while (Q.size() && A[i] >= A[Q.back()])
			Q.pop_back();
		Q.push_back(i);
	}
	for (int i = k - 1; i < len; ++i)
	{
		while (Q.size() && A[i] >= A[Q.back()])
			Q.pop_back();
		Q.push_back(i);
		R.push_back(A[Q.front()]);
		while (Q.size() && Q.front() <= i - k + 1)
			Q.pop_front();
	}
	return R;
}


int main()
{
	vector<int>
		a = { 1, 3, -1, -3, 5, 3, 6, 7 },
		b = { 7, 2, 4 };
	output(maxSlidingWindow(b, 2));
	output(maxSlidingWindow(a, 3));
}
