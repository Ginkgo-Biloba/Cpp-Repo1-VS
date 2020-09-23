#include "leetcode.hpp"

/* 840. 矩阵中的幻方

3 x 3 的幻方是一个填充有从 1 到 9 的不同数字的 3 x 3 矩阵，其中每行，每列以及两条对角线上的各数之和都相等。

给定一个由整数组成的 grid，其中有多少个 3 × 3 的 “幻方” 子矩阵？（每个子矩阵都是连续的）。

示例：
输入:
[[4,3,8,4],
 [9,5,1,9],
 [2,7,6,2]]
输出: 1
解释:
下面的子矩阵是一个 3 x 3 的幻方：
438
951
276

而这一个不是：
384
519
762

总的来说，在本示例所给定的矩阵中只有一个 3 x 3 的幻方子矩阵。

提示:
	1 <= grid.length <= 10
	1 <= grid[0].length <= 10
	0 <= grid[i][j] <= 15
*/

//leetcode-cn.com/problems/magic-squares-in-grid/solution/-ju-zhen-zhong-de-huan-fang-by-hareyukai/
// 抄的
int numMagicSquaresInside(vector<vector<int>>& grid)
{
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	if (rows < 3 || cols < 3)
		return 0;

	int64_t const valid[8] = {
		0x276951438,
		0x294753618,
		0x438951276,
		0x492357816,
		0x618753294,
		0x672159834,
		0x816357492,
		0x834159672,
	};
	int count = 0;
	for (int h = 2; h < rows; ++h)
		for (int w = 2; w < cols; ++w)
		{
			int64_t s = 0;
			for (int y = -2; y <= 0; ++y)
				for (int x = -2; x <= 0; ++x)
					s = (s << 4) | static_cast<unsigned>(grid[h + y][w + x]);
			if (std::binary_search(valid, valid + 8, s))
				++count;
		}
	return count;
}

int main()
{}
