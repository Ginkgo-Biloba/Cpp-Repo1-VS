#include "leetcode.hpp"

/* 329. 矩阵中的最长递增路径

给定一个整数矩阵，找出最长递增路径的长度。

对于每个单元格，你可以往上，下，左，右四个方向移动。
你不能在对角线方向上移动或移动到边界外（即不允许环绕）。

示例 1:
输入: nums =
[
	[9,9,4],
	[6,6,8],
	[2,1,1]
]
输出: 4
解释: 最长递增路径为 [1, 2, 6, 9]。

示例 2:
输入: nums =
[
	[3,4,5],
	[3,2,6],
	[2,2,1]
]
输出: 4
解释: 最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。
*/

// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/discuss/288520/BFS-Implemented-Topological-Sort
// 抄的
class Solution
{
	struct Point
	{
		unsigned y, x;
	};

public:
	int longestIncreasingPath(vector<vector<int>>& matrix)
	{
		int const dir[] = { -1, 0, 1, 0, -1 };
		unsigned rows = static_cast<unsigned>(matrix.size());
		if (rows == 0) return 0;
		unsigned cols = static_cast<unsigned>(matrix[0].size());
		if (cols == 0) return 0;
		vector<vector<int>> ind = matrix;
		for (unsigned h = 0; h != rows; ++h)
			for (unsigned w = 0; w != cols; ++w)
			{
				ind[h][w] = 0;
				for (int d = 0; d < 4; ++d)
				{
					unsigned y = h + dir[d];
					unsigned x = w + dir[d + 1];
					if ((y < rows) && (x < cols)
						&& (matrix[y][x] > matrix[h][w]))
						ind[h][w] += 1;
				}
			}

		vector<Point> curr, temp;
		for (unsigned h = 0; h != rows; ++h)
			for (unsigned w = 0; w != cols; ++w)
			{
				if (ind[h][w] == 0)
					curr.push_back({ h, w });
			}

		int ans = 0;
		for (; !curr.empty(); ++ans)
		{
			temp.clear();
			for (Point& p : curr)
				for (int d = 0; d < 4; ++d)
				{
					unsigned y = p.y + dir[d];
					unsigned x = p.x + dir[d + 1];
					if ((y < rows) && (x < cols)
						&& (matrix[p.y][p.x] > matrix[y][x]))
					{
						if (--(ind[y][x]) == 0)
							temp.push_back({ y, x });
					}
				}
			curr.swap(temp);
		}
		return ans;
	}
};


int main()
{
	vector<vector<int>>
		a = {
			{ 9, 9, 4 },
			{ 6, 6, 8 },
			{ 2, 1, 1 },
	},
	b = {
		{ 3, 4, 5 },
		{ 3, 2, 6 },
		{ 2, 2, 1 },
	};
	Solution s;
	OutExpr(s.longestIncreasingPath(a), "%d");
	OutExpr(s.longestIncreasingPath(b), "%d");
}
