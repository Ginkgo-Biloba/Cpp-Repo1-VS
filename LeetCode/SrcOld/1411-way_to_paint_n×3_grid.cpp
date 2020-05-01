#include "leetcode.hpp"

/* 1411. 给 N x 3 网格图涂色的方案数

你有一个 n x 3 的网格图 grid ，你需要用 红，黄，绿 三种颜色之一给每一个格子上色，且确保相邻格子颜色不同（也就是有相同水平边或者垂直边的格子颜色不同）。

给你网格图的行数 n 。
请你返回给 grid 涂色的方案数。
由于答案可能会非常大，请你返回答案对 10^9 + 7 取余的结果。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/04/12/e1.png
输入：n = 1
输出：12
解释：总共有 12 种可行的方法：

示例 2：
输入：n = 2
输出：54

示例 3：
输入：n = 3
输出：246

示例 4：
输入：n = 7
输出：106494

示例 5：
输入：n = 5000
输出：30228214

提示：
	n == grid.length
	grid[i].length == 3
	1 <= n <= 5000
*/


class Solution
{
public:
	int numOfWays_Org(int n)
	{
		int64_t const Mod = 1e9 + 7;
		vector<int64_t> A(12, 1), B(12);
		for (--n; n > 0; --n)
		{
			B[0] = (A[4] + A[5] + A[7] + A[8] + A[9]) % Mod;
			B[1] = (A[4] + A[6] + A[7] + A[8]) % Mod;
			B[2] = (A[4] + A[5] + A[8] + A[9] + A[11]) % Mod;
			B[3] = (A[5] + A[9] + A[10] + A[11]) % Mod;
			B[4] = (A[0] + A[1] + A[2] + A[10] + A[11]) % Mod;
			B[5] = (A[0] + A[2] + A[3] + A[10]) % Mod;
			B[6] = (A[1] + A[8] + A[9] + A[11]) % Mod;
			B[7] = (A[0] + A[1] + A[9] + A[10] + A[11]) % Mod;
			B[8] = (A[0] + A[1] + A[2] + A[6]) % Mod;
			B[9] = (A[0] + A[2] + A[3] + A[6] + A[7]) % Mod;
			B[10] = (A[3] + A[4] + A[5] + A[7]) % Mod;
			B[11] = (A[2] + A[3] + A[4] + A[6] + A[7]) % Mod;
			B.swap(A);
		}
		for (int i = 1; i < 12; ++i)
			A[0] += A[i];
		return static_cast<int>(A[0] % Mod);
	}

	// https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/discuss/574923/JavaC%2B%2BPython-DP-O(1)-Space
	// 抄的
	int numOfWays(int n)
	{
		int64_t const Mod = 1e9 + 7;
		int64_t a121 = 6, a123 = 6, b121, b123;
		for (int i = 1; i < n; ++i)
		{
			b121 = a121 * 3 + a123 * 2;
			b123 = a121 * 2 + a123 * 2;
			a121 = b121 % Mod;
			a123 = b123 % Mod;
		}
		return static_cast<int>((a121 + a123) % Mod);
	}
};


int main()
{
	Solution s;
	OutExpr(s.numOfWays(1), "%d");
	OutExpr(s.numOfWays(2), "%d");
	OutExpr(s.numOfWays(3), "%d");
	OutExpr(s.numOfWays(7), "%d");
	OutExpr(s.numOfWays(5000), "%d");
}
