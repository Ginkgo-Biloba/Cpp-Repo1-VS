#include "leetcode.hpp"

/* 1020. 飞地的数量

给出一个二维数组 A，每个单元格为 0（代表海）或 1（代表陆地）。

移动是指在陆地上从一个地方走到另一个地方（朝四个方向之一）或离开网格的边界。

返回网格中无法在任意次数的移动中离开网格边界的陆地单元格的数量。

示例 1：
输入：[[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
输出：3
解释：
有三个 1 被 0 包围。一个 1 没有被包围，因为它在边界上。

示例 2：
输入：[[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
输出：0
解释：
所有 1 都在边界上或可以到达边界。

提示：
	1 <= A.length <= 500
	1 <= A[i].length <= 500
	0 <= A[i][j] <= 1
	所有行的大小都相同
*/

void bfs(vector<vector<int>>& A, int y, int x)
{
	int const dir[] = { -1, 0, 1, 0, -1 };
	unsigned rows = static_cast<unsigned>(A.size());
	unsigned cols = static_cast<unsigned>(A[0].size());
	vector<pair<int, int>> current, nextstep;
	current.emplace_back(y, x);
	A[y][x] = 0;
	while (!current.empty())
	{
		nextstep.clear();
		for (auto const& p : current)
			for (int d = 0; d < 4; ++d)
			{
				y = p.first + dir[d];
				x = p.second + dir[d + 1];
				if (static_cast<unsigned>(y) >= rows
					|| static_cast<unsigned>(x) >= cols
					|| A[y][x] != 1)
					continue;
				A[y][x] = 0;
				nextstep.emplace_back(y, x);
			}
		nextstep.swap(current);
	}
}


int numEnclaves(vector<vector<int>>& A)
{
	int rows = static_cast<unsigned>(A.size());
	int cols = static_cast<unsigned>(A[0].size());
	int nums = 0;
	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
		{
			if ((0 < h) && (h < rows - 1) && (w == 1))
				w = cols - 1;
			if (A[h][w] != 0)
				bfs(A, h, w);
		}
	for (int h = 1; h < rows - 1; ++h)
	{
		for (int w = 1; w < cols - 1; ++w)
			nums += A[h][w];
	}
	return nums;
}


int main()
{
	vector<vector<int>>
		a = { { 0, 0, 0, 0 }, { 1, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 } },
		b = { { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 0 } };
	OutExpr(numEnclaves(a), "%d");
	OutExpr(numEnclaves(b), "%d");
}
