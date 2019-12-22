#include "leetcode.hpp"

/* 892. 三维形体的表面积

在 N * N 的网格上，我们放置一些 1 * 1 * 1  的立方体。

每个值 v = grid[i][j] 表示 v 个正方体叠放在对应单元格 (i, j) 上。

请你返回最终形体的表面积。

示例 1：
输入：[[2]]
输出：10

示例 2：
输入：[[1,2],[3,4]]
输出：34

示例 3：
输入：[[1,0],[0,2]]
输出：16

示例 4：
输入：[[1,1,1],[1,0,1],[1,1,1]]
输出：32

示例 5：
输入：[[2,2,2],[2,1,2],[2,2,2]]
输出：46

提示：
	1 <= N <= 50
	0 <= grid[i][j] <= 50
*/

// https://leetcode.com/problems/surface-area-of-3d-shapes/discuss/163414/C%2B%2BJava1-line-Python-Minus-Hidden-Area
// 抄的
int surfaceArea(vector<vector<int>>& grid)
{
	int S = 0;
	int N = static_cast<int>(grid.size());
	for (int h = 0; h < N; ++h)
		for (int w = 0; w < N; ++w)
		{
			if (grid[h][w])
				S += 4 * grid[h][w] + 2;
			if (h)
				S -= 2 * std::min(grid[h][w], grid[h - 1][w]);
			if (w)
				S -= 2 * std::min(grid[h][w], grid[h][w - 1]);
		}
	return S;
}


int main()
{
	vector<vector<int>>
		a = { { 2 } },
		b = { { 1, 2 }, { 3, 4 } },
		c = { { 1, 0 }, { 0, 2 } },
		d = { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } },
		e = { { 2, 2, 2 }, { 2, 1, 2 }, { 2, 2, 2 } };
	OutExpr(surfaceArea(a), "%d");
	OutExpr(surfaceArea(b), "%d");
	OutExpr(surfaceArea(c), "%d");
	OutExpr(surfaceArea(d), "%d");
	OutExpr(surfaceArea(e), "%d");
}
