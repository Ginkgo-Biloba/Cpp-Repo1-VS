#include "leetcode.hpp"

/* 130. 被围绕的区域

给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。

找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

示例:

X X X X
X O O X
X X O X
X O X X

运行你的函数后，矩阵变为：

X X X X
X X X X
X X X X
X O X X

解释:
被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。
任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。
如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。
*/

class Solution
{
	vector<vector<char>> grid;
	vector<pair<int, int>> A, B;
	int rows, cols;

	void bfs(int h, int w)
	{
		int const dir[] = { -1, 0, 1, 0, -1 };
		A.emplace_back(h, w);
		grid[h][w] = 'A';
		while (!A.empty())
		{
			B.clear();
			for (auto const& a : A)
				for (int d = 0; d < 4; ++d)
				{
					h = a.first + dir[d];
					w = a.second + dir[d + 1];
					if (static_cast<unsigned>(h) < static_cast<unsigned>(rows)
						&& static_cast<unsigned>(w) < static_cast<unsigned>(cols)
						&& grid[h][w] == 'O')
					{
						B.emplace_back(h, w);
						grid[h][w] = 'A';
					}
				}
			B.swap(A);
		}
	}

public:
	void solve(vector<vector<char>>& board)
	{
		if (board.empty() || board[0].empty())
			return;

		grid.swap(board);
		rows = static_cast<int>(grid.size());
		cols = static_cast<int>(grid[0].size());
		for (int w = 0; w < cols; ++w)
		{
			if (grid[0][w] == 'O')
				bfs(0, w);
			if (grid[rows - 1][w] == 'O')
				bfs(rows - 1, w);
		}
		for (int h = 1; h < rows - 1; ++h)
		{
			if (grid[h][0] == 'O')
				bfs(h, 0);
			if (grid[h][cols - 1] == 'O')
				bfs(h, cols - 1);
		}
		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
			{
				if (grid[h][w] == 'O')
					grid[h][w] = 'X';
				else if (grid[h][w] == 'A')
					grid[h][w] = 'O';
			}

		grid.swap(board);
	}
};


int main()
{}
