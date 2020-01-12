#include "leetcode.hpp"

/* 962. 最大宽度坡

给定一个整数数组 A，坡是元组 (i, j)，其中  i < j 且 A[i] <= A[j]。
这样的坡的宽度为 j - i。

找出 A 中的坡的最大宽度，如果不存在，返回 0 。

示例 1：
输入：[6,0,8,2,1,5]
输出：4
解释：
最大宽度的坡为 (i, j) = (1, 5): A[1] = 0 且 A[5] = 5.

示例 2：
输入：[9,8,1,0,1,9,4,0,4,1]
输出：7
解释：
最大宽度的坡为 (i, j) = (2, 9): A[2] = 1 且 A[9] = 1.

提示：
	2 <= A.length <= 50000
	0 <= A[i] <= 50000
*/

struct Cmper
{
	int const* A;

	Cmper(int const* a)
		: A(a)
	{}

	bool operator()(int const& x, int const& y) const
	{
		return A[x] > A[y];
	}
};

int maxWidthRamp1(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int ans = 0;
	vector<int> idx;
	Cmper cmper(A.data());
	idx.reserve(len);

	for (int i = 0; i < len; ++i)
	{
		auto it = lower_bound(idx.begin(), idx.end(), i, cmper);
		if (it != idx.end())
			ans = max(ans, i - *it);
		else
			idx.push_back(i);
	}

	return ans;
}

// https://leetcode.com/problems/maximum-width-ramp/discuss/208348/JavaC%2B%2BPython-O(N)-Using-Stack
// 抄的
int maxWidthRamp(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int ans = 0;
	vector<int> idx;
	idx.reserve(len);

	// 记住关键的递减坐标
	for (int i = 0; i < len; ++i)
	{
		if (idx.empty() || A[idx.back()] > A[i])
			idx.push_back(i);
	}

	// 从后往前遍历前面所有小于当前数的坐标
	for (int i = len - 1; i > ans; --i)
		while (!idx.empty() && A[idx.back()] <= A[i])
		{
			ans = max(ans, i - idx.back()),
				idx.pop_back();
		}

	return ans;
}


int main()
{
	vector<int>
		a = { 6, 0, 8, 2, 1, 5 },
		b = { 9, 8, 1, 0, 1, 9, 4, 0, 4, 1 };
	OutExpr(maxWidthRamp(a), "%d");
	OutExpr(maxWidthRamp(b), "%d");
}
