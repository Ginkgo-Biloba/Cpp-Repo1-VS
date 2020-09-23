#include "leetcode.hpp"

/* 164. 最大间距

给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。

如果数组元素个数小于 2，则返回 0。

示例 1:

输入: [3,6,9,1]
输出: 3
解释: 排序后的数组是 [1,3,6,9], 其中相邻元素 (3,6) 和 (6,9) 之间都存在最大差值 3。

示例 2:

输入: [10]
输出: 0
解释: 数组元素个数小于 2，因此返回 0。

说明:
	你可以假设数组中所有元素都是非负整数，且数值在 32 位有符号整数范围内。
	请尝试在线性时间复杂度和空间复杂度的条件下解决此问题。
*/

// https://leetcode-cn.com/problems/maximum-gap/solution/zui-da-jian-ju-by-leetcode/
// 基数排序是 O(NlogN) 不能用
// 抄的
struct Bucket
{
	int a, b;
	Bucket() : a(INT_MAX), b(0) {}
};

int maximumGap(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	if (len < 2)
		return 0;
	int ans = A[0], pre = A[0];

	for (int i = 1; i < len; ++i)
	{
		ans = max(ans, A[i]);
		pre = min(pre, A[i]);
	}

	int width = max(1, (ans - pre) / (len - 1));
	int count = (ans - pre) / width + 1;
	vector<Bucket> bucket(count);
	vector<char> used(count);

	for (int i = 0; i < len; ++i)
	{
		int n = (A[i] - pre) / width;
		used[n] = 1;
		bucket[n].a = min(bucket[n].a, A[i]);
		bucket[n].b = max(bucket[n].b, A[i]);
	}

	ans = 0;
	for (int i = 0; i < count; ++i)
	{
		if (!(used[i]))
			continue;
		ans = max(ans, bucket[i].a - pre);
		pre = bucket[i].b;
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 3, 6, 9, 1 },
		b = { 10, 10 },
		c = { 1, 5, 1, 5, 5, 1, 1 };
	OutExpr(maximumGap(a), "%d");
	OutExpr(maximumGap(b), "%d");
	OutExpr(maximumGap(c), "%d");
}
