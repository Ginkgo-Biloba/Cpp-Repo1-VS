#include "leetcode.hpp"

/* 1504. 统计全 1 子矩形

给你一个只包含 0 和 1 的 rows * columns 矩阵 mat ，请你返回有多少个 子矩形 的元素全部都是 1 。

示例 1：
输入：mat = [
	[1,0,1],
	[1,1,0],
	[1,1,0]
]
输出：13
解释：
有 6 个 1x1 的矩形。
有 2 个 1x2 的矩形。
有 3 个 2x1 的矩形。
有 1 个 2x2 的矩形。
有 1 个 3x1 的矩形。
矩形数目总共 = 6 + 2 + 3 + 1 + 1 = 13 。

示例 2：
输入：mat = [
	[0,1,1,0],
	[0,1,1,1],
	[1,1,1,0]
]
输出：24
解释：
有 8 个 1x1 的子矩形。
有 5 个 1x2 的子矩形。
有 2 个 1x3 的子矩形。
有 4 个 2x1 的子矩形。
有 2 个 2x2 的子矩形。
有 2 个 3x1 的子矩形。
有 1 个 3x2 的子矩形。
矩形数目总共 = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24 。

示例 3：
输入：mat = [[1,1,1,1,1,1]]
输出：21

示例 4：
输入：mat = [[1,0,1],[0,1,0],[1,0,1]]
输出：5

提示：
	1 <= rows <= 150
	1 <= columns <= 150
	0 <= mat[i][j] <= 1
*/

int numSubmat(vector<vector<int>>& M)
{
	int rows = static_cast<int>(M.size());
	int cols = static_cast<int>(M[0].size());
	vector<vector<int>> H = M;
	for (int h = 0; h < rows; ++h)
		for (int w = 1; w < cols; ++w)
		{
			if (H[h][w] == 1)
				H[h][w] += H[h][w - 1];
		}

	int ans = 0, hori;
	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
		{
			if (M[h][w] == 0)
				continue;
			ans += H[h][w];
			hori = H[h][w];
			for (int u = h - 1; u >= 0; --u)
			{
				hori = min(hori, H[u][w]);
				if (hori == 0)
					break;
				ans += hori;
			}
		}
	return ans;
}

int main()
{}
