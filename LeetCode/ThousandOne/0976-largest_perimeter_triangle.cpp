#include "leetcode.hpp"

/* 976. 三角形的最大周长

给定由一些正数（代表长度）组成的数组 A，返回由其中三个长度组成的、面积不为零的三角形的最大周长。

如果不能形成任何面积不为零的三角形，返回 0。

示例 1：
输入：[2,1,2]
输出：5

示例 2：
输入：[1,2,1]
输出：0

示例 3：
输入：[3,2,3,4]
输出：10

示例 4：
输入：[3,6,2,3]
输出：8

提示：
	3 <= A.length <= 10000
	1 <= A[i] <= 10^6
*/

int largestPerimeter(vector<int>& A)
{
	int n = static_cast<int>(A.size());
	sort(A.begin(), A.end());
	for (int i = n - 3; i >= 0; --i)
	{
		if (A[i] + A[i + 1] > A[i + 2])
			return A[i] + A[i + 1] + A[i + 2];
	}
	return 0;
}


int main()
{
	vector<int>
		a = { 2, 1, 2 },
		b = { 1, 2, 1 },
		c = { 3, 2, 3, 4 },
		d = { 3, 6, 2, 3 };
	OutExpr(largestPerimeter(a), "%d");
	OutExpr(largestPerimeter(b), "%d");
	OutExpr(largestPerimeter(c), "%d");
	OutExpr(largestPerimeter(d), "%d");
}
