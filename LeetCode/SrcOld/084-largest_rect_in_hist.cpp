#include "leetcode.hpp"

/* 84. 柱状图中最大的矩形

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

https://assets.leetcode.com/uploads/2018/10/12/histogram.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/histogram.png

以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。

https://assets.leetcode.com/uploads/2018/10/12/histogram_area.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/histogram_area.png
图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。

示例:

输入: [2,1,5,6,2,3]
输出: 10
*/

int largestRectangleArea(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	if (len == 0)
		return 0;
	int ans = 0, cur;
	vector<int> L(len), R(len), S;
	for (int i = 0; i < len; ++i)
	{
		while (!S.empty() && A[S.back()] >= A[i])
			S.pop_back();
		L[i] = S.empty() ? -1 : S.back();
		S.push_back(i);
	}
	S.clear();
	for (int i = len - 1; i >= 0; --i)
	{
		while (!S.empty() && A[S.back()] >= A[i])
			S.pop_back();
		R[i] = S.empty() ? len : S.back();
		S.push_back(i);
	}
	for (int i = 0; i < len; ++i)
	{
		cur = A[i] * (R[i] - L[i] - 1);
		ans = max(ans, cur);
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 2, 1, 5, 6, 2, 3 },
		b = { 1 },
		c = { 0, 1 };
	OutExpr(largestRectangleArea(a), "%d");
	OutExpr(largestRectangleArea(b), "%d");
	OutExpr(largestRectangleArea(c), "%d");
}
