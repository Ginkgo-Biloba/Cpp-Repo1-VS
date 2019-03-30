#include "../srcOld/utility.hpp"

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

class Solution
{
	vector<vector<int>> mat;
	vector<int> cache;
	unsigned rows, cols;
	int ans;

	int dfs(unsigned y, unsigned x)
	{
		unsigned const dir[4][2] = { 
			{ 0, 1 }, { 0, (unsigned)(-1) }, 
			{ (unsigned)(-1), 0 }, { 1, 0 } };

		unsigned icur = y * cols + x;
		if (cache[icur] != 0)
			return cache[icur];

		int curlen = 1;
		for (int i = 0; i < 4; ++i)
		{
			unsigned cx = x + dir[i][0], cy = y + dir[i][1];
			if (cy < rows && cx < cols && mat[cy][cx] > mat[y][x])
			{
				int len = 1 + dfs(cy, cx);
				curlen = std::max(curlen, len);
			}
		}
		cache[icur] = curlen;
		return curlen;
	}
public:

	int longestIncreasingPath(vector<vector<int>>& matrix)
	{
		mat.swap(matrix);
		rows = mat.size();
		if (rows == 0) return 0;
		cols = mat[0].size();
		if (cols == 0) return 0;

		if (cache.size() < rows * cols)
			cache.resize(rows * cols);
		memset(cache.data(), 0, rows * cols * sizeof(int));

		for (unsigned y = 0; y < rows; ++y)
			for (unsigned x = 0; x < cols; ++x)
			{
				int len = dfs(y, x);
				ans = std::max(ans, len);
			}

		return ans;
	}
};


int main()
{
	vector<vector<int>> matrix =
	{
		{ 9, 9, 4 },
		{ 6, 6, 8 },
		{ 2, 1, 1 },
	};

	int len = Solution().longestIncreasingPath(matrix);
	printf("longestIncreasingPath: %d\n", len);
}
