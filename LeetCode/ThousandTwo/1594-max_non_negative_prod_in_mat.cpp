#include "leetcode.hpp"

/* 1594. 矩阵的最大非负积

给你一个大小为 rows x cols 的矩阵 grid 。
最初，你位于左上角 (0, 0) ，每一步，你可以在矩阵中 向右 或 向下 移动。

在从左上角 (0, 0) 开始到右下角 (rows - 1, cols - 1) 结束的所有路径中，找出具有 最大非负积 的路径。
路径的积是沿路径访问的单元格中所有整数的乘积。

返回 最大非负积 对 109 + 7 取余 的结果。
如果最大积为负数，则返回 -1 。

注意，取余是在得到最大积之后执行的。

示例 1：

输入：grid =
[
	[-1,-2,-3],
	[-2,-3,-3],
	[-3,-3,-2]
]
输出：-1
解释：从 (0, 0) 到 (2, 2) 的路径中无法得到非负积，所以返回 -1

示例 2：

输入：grid =
[
	[1,-2,1],
	[1,-2,1],
	[3,-4,1]
]
输出：8
解释：最大非负积对应的路径已经用粗体标出 (1 * 1 * -2 * -4 * 1 = 8)

示例 3：

输入：grid =
[
	[1, 3],
	[0,-4]
]
输出：0
解释：最大非负积对应的路径已经用粗体标出 (1 * 0 * -4 = 0)

示例 4：

输入：grid =
[
	[ 1, 4,4,0],
	[-2, 0,0,1],
	[ 1,-1,1,1]
]
输出：2
解释：最大非负积对应的路径已经用粗体标出 (1 * -2 * 1 * -1 * 1 * 1 = 2)

提示：
	1 <= rows, cols <= 15
	-4 <= grid[i][j] <= 4
*/

class Solution
{
public:
	int maxProductPath(vector<vector<int>>& grid)
	{
		int rows = static_cast<int>(grid.size());
		int cols = static_cast<int>(grid[0].size());
		vector<array<int64_t, 2>> mat(rows * cols);
		mat[0][0] = mat[0][1] = grid[0][0];

		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
			{
				if (h == 0 && w == 0)
					continue;
				int i = h * cols + w;
				int cur = grid[h][w];
				int64_t x = INT64_MIN, y = INT_MAX;
				int64_t z;
				if (h > 0)
				{
					z = mat[i - cols][0] * cur;
					x = max(x, z);
					y = min(y, z);
					z = mat[i - cols][1] * cur;
					x = max(x, z);
					y = min(y, z);
				}
				if (w > 0)
				{
					z = mat[i - 1][0] * cur;
					x = max(x, z);
					y = min(y, z);
					z = mat[i - 1][1] * cur;
					x = max(x, z);
					y = min(y, z);
				}
				mat[i][0] = max(x, y);
				mat[i][1] = min(x, y);
			}

		int64_t ans = mat.back()[0];
		if (ans < 0)
			ans = -1;
		else
			ans %= static_cast<int64_t>(1e9 + 7);
		return static_cast<int>(ans);
	}
};


int main()
{}
