#include "leetcode.hpp"

/* 1494. 并行课程 II

给你一个整数 n 表示某所大学里课程的数目，编号为 1 到 n ，数组 dependencies 中， dependencies[i] = [xi, yi]  表示一个先修课的关系，也就是课程 xi 必须在课程 yi 之前上。
同时你还有一个整数 k 。

在一个学期中，你 最多 可以同时上 k 门课，前提是这些课的先修课在之前的学期里已经上过了。

请你返回上完所有课最少需要多少个学期。
题目保证一定存在一种上完所有课的方式。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/27/leetcode_parallel_courses_1.png
输入：n = 4, dependencies = [[2,1],[3,1],[1,4]], k = 2
输出：3
解释：上图展示了题目输入的图。
在第一个学期中，我们可以上课程 2 和课程 3 。
然后第二个学期上课程 1 ，第三个学期上课程 4 。

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/27/leetcode_parallel_courses_2.png
输入：n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2
输出：4
解释：上图展示了题目输入的图。
一个最优方案是：第一学期上课程 2 和 3，第二学期上课程 4 ，第三学期上课程 1 ，第四学期上课程 5 。

示例 3：
输入：n = 11, dependencies = [], k = 2
输出：6

提示：
	1 <= n <= 15
	1 <= k <= n
	0 <= dependencies.length <= n * (n-1) / 2
	dependencies[i].length == 2
	1 <= xi, yi <= n
	xi != yi
	所有先修关系都是不同的，也就是说 dependencies[i] != dependencies[j] 。
	题目输入的图是个有向无环图。
*/

unsigned popcnt(unsigned n)
{
#if defined _MSC_VER
	return __popcnt(n);
#elif defined __GNUC__
	return __builtin_popcount(n);
#else
	n = n - ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n + (n >> 4)) & 0x0f0f0f0f;
	n = (n * 0x1010101) >> 24;
	return n;
#endif
}

// https://leetcode.com/problems/parallel-courses-ii/discuss/709382/C%2B%2B-O(3n)-bitmask-dynamic-programming-code-with-comments-and-tutorial
// 抄的
int minNumberOfSemesters(int n, vector<vector<int>>& depend, int k)
{
	int Z = 1 << n;
	vector<int> dep(n);
	for (auto& d : depend)
		dep[d[1] - 1] |= 1 << (d[0] - 1);

	// 状态 i 的前提条件
	vector<int> pre(Z);
	for (int i = 0; i < Z; ++i)
		for (int m = 0; m < n; ++m)
		{
			if (i & (1 << m))
				pre[i] |= dep[m];
		}

	// 状态 i 的结果，是 1 的那些位还没有上课
	vector<int> dp(Z, n + 1);
	dp[0] = 0;
	for (int i = 0; i < Z; ++i)
	{
		for (int m = i; m > 0; m = (m - 1) & i)
		{
			if (static_cast<int>(popcnt(m)) > k)
				continue;
			int taken = i ^ (Z - 1);
			if ((taken & pre[m]) == pre[m])
				dp[i] = min(dp[i], dp[i ^ m] + 1);
		}
	}
	return dp[Z - 1];
}

int main()
{
	vector<vector<int>>
		a = { { 2, 1 }, { 3, 1 }, { 1, 4 } },
		b = { { 2, 1 }, { 3, 1 }, { 4, 1 }, { 1, 5 } },
		c;
	OutExpr(minNumberOfSemesters(4, a, 2), "%d");
	OutExpr(minNumberOfSemesters(5, b, 2), "%d");
	OutExpr(minNumberOfSemesters(11, c, 2), "%d");
}
