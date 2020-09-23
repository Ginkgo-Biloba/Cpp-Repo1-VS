#include "leetcode.hpp"

/* 1091. 二进制矩阵中的最短路径

在一个 N × N 的方形网格中，每个单元格有两种状态：空（0）或者阻塞（1）。

一条从左上角到右下角、长度为 k 的畅通路径，由满足下述条件的单元格 C_1, C_2, ..., C_k 组成：

	相邻单元格 C_i 和 C_{i+1} 在八个方向之一上连通（此时，C_i 和 C_{i+1} 不同且共享边或角）
	C_1 位于 (0, 0)（即，值为 grid[0][0]）
	C_k 位于 (N-1, N-1)（即，值为 grid[N-1][N-1]）
	如果 C_i 位于 (r, c)，则 grid[r][c] 为空（即，grid[r][c] == 0）

返回这条从左上角到右下角的最短畅通路径的长度。如果不存在这样的路径，返回 -1 。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/06/16/example1_2.png
输入：[[0,1],[1,0]]
输出：2

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/06/16/example2_2.png
输入：[[0,0,0],[1,1,0],[1,1,0]]
输出：4

提示：
	1 <= grid.length == grid[0].length <= 100
	grid[i][j] 为 0 或 1
*/


class Solution
{
public:
	int shortestPathBinaryMatrix(vector<vector<int>>& grid)
	{
		int rows = static_cast<int>(grid.size());
		int cols = static_cast<int>(grid[0].size());
		vector<pair<int, int>> current, nextloop;
		if (grid[0][0] == 0)
		{
			if (rows == 1 && cols == 1)
				return 1;
			current.emplace_back(0, 0);
			grid[0][0] = 1;
		}

		for (int s = 2; !current.empty(); ++s)
		{
			nextloop.clear();
			for (auto const& cur : current)
				for (int y = -1; y <= 1; ++y)
					for (int x = -1; x <= 1; ++x)
					{
						int h = y + cur.first;
						int w = x + cur.second;
						if (static_cast<unsigned>(h) < static_cast<unsigned>(rows)
							&& static_cast<unsigned>(w) < static_cast<unsigned>(cols)
							&& grid[h][w] == 0)
						{
							if (h == rows - 1 && w == cols - 1)
								return s;
							grid[h][w] = s;
							nextloop.emplace_back(h, w);
						}
					}
			nextloop.swap(current);
		}

		return -1;
	}
};


int main()
{}
