#include "leetcode.hpp"

/* 120. 三角形最小路径和

给定一个三角形，找出自顶向下的最小路径和。
每一步只能移动到下一行中相邻的结点上。

例如，给定三角形：

> [
>      [2],
>     [3,4],
>    [6,5,7],
>   [4,1,8,3]
> ]

自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

说明：
如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。
*/

int adds(int a, int b)
{
	if (a > 0)
	{
		if (b > INT_MAX - a)
			return INT_MAX;
	}
	else if (b < INT_MIN - a)
		return INT_MIN;
	return a + b;
}

int minimumTotal(vector<vector<int>>& triangle)
{
	int rows = static_cast<int>(triangle.size());
	int *A, *B, ans = INT_MAX;
	if (rows == 0)
		return 0;
	if (rows == 1)
		return triangle[0][0];
	for (int h = 1; h < rows; ++h)
	{
		A = triangle[h - 1].data();
		B = triangle[h].data();
		B[0] = adds(B[0], A[0]);
		B[h] = adds(B[h], A[h - 1]);
		for (int w = 1; w < h; ++w)
			B[w] = adds(B[w], min(A[w - 1], A[w]));
	}
	for (int w = 0; w <= rows; ++w)
		ans = min(ans, B[w]);
	return ans;
}


int main()
{
	OutExpr(adds(-2, 3), "%d");
	OutExpr(adds(-2, INT_MIN), "%d");
	OutExpr(adds(INT_MAX, 3), "%d");
	OutExpr(adds(INT_MIN + 2, 3), "%d");
}
