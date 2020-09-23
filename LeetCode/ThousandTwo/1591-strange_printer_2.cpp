#include "leetcode.hpp"

/* 1591. 奇怪的打印机 II

给你一个奇怪的打印机，它有如下两个特殊的打印规则：
	每一次操作时，打印机会用同一种颜色打印一个矩形的形状，每次打印会覆盖矩形对应格子里原本的颜色。
	一旦矩形根据上面的规则使用了一种颜色，那么 相同的颜色不能再被使用 。

给你一个初始没有颜色的 m x n 的矩形 targetGrid ，其中 targetGrid[row][col] 是位置 (row, col) 的颜色。

如果你能按照上述规则打印出矩形 targetGrid ，请你返回 true ，否则返回 false 。

示例 1：
https://assets.leetcode.com/uploads/2020/08/15/sample_1_1929.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/09/19/sample_1_1929.png
输入：targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
输出：true

示例 2：
https://assets.leetcode.com/uploads/2020/08/15/sample_2_1929.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/09/19/sample_2_1929.png
输入：targetGrid = [[1,1,1,1],[1,1,3,3],[1,1,3,4],[5,5,1,4]]
输出：true

示例 3：
输入：targetGrid = [[1,2,1],[2,1,2],[1,2,1]]
输出：false
解释：没有办法得到 targetGrid ，因为每一轮操作使用的颜色互不相同。

示例 4：
输入：targetGrid = [[1,1,1],[3,1,3]]
输出：false

提示：
	m == targetGrid.length
	n == targetGrid[i].length
	1 <= m, n <= 60
	1 <= targetGrid[row][col] <= 60
*/

// https://leetcode.com/problems/strange-printer-ii/discuss/854193/Python-Straight-Forward
// 抄的
bool isPrintable(vector<vector<int>>& grid)
{
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());
	// xmin, xmax, ymin, ymax;
	int rect[60][4];
	memset(rect, 0xff, sizeof(rect));

	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
		{
			int c = grid[h][w] - 1;
			int* R = rect[c];
			if (R[0] < 0)
			{
				R[0] = R[1] = w;
				R[2] = R[3] = h;
			}
			else
			{
				R[0] = min(R[0], w);
				R[1] = max(R[1], w);
				R[2] = min(R[2], h);
				R[3] = max(R[3], h);
			}
		}

	// for every cell, check other colors (60) covery it or not
	// instead of checking rect convered by its color (up to 60^2)
	int64_t after[60] = { 0 };
	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
		{
			int k = grid[h][w] - 1;
			for (int i = 0; i < 60; ++i)
			{
				if (i == k)
					continue;
				int* R = rect[i];
				if (R[0] <= w && w <= R[1] && R[2] <= h && h <= R[3])
					after[i] |= INT64_C(1) << k;
			}
		}

	// topplogical sort
	int indeg[60];
	vector<int> proc;
	size_t idx = 0;
	for (int i = 0; i < 60; ++i)
	{
		// check any color need to print befor i
		indeg[i] = 0;
		for (int k = 0; k < 60; ++k)
		{
			if (after[k] & (INT64_C(1) << i))
				++(indeg[i]);
		}
		if (indeg[i] == 0)
			proc.push_back(i);
	}
	for (; idx < proc.size(); ++idx)
	{
		int64_t a = after[proc[idx]];
		if (a == 0)
			continue;
		for (int i = 0; i < 60; ++i)
			if (a & (INT64_C(1) << i))
			{
				if ((--indeg[i]) == 0)
					proc.push_back(i);
			}
	}

	// check every color is processed or not
	for (int i = 0; i < 60; ++i)
	{
		if (indeg[i])
			return false;
	}
	return true;
}


int main()
{
	vector<vector<int>>
		a = {
			{ 1, 1, 1, 1 },
			{ 1, 2, 2, 1 },
			{ 1, 2, 2, 1 },
			{ 1, 1, 1, 1 },
	},
	b = {
		{ 1, 1, 1, 1 },
		{ 1, 1, 3, 3 },
		{ 1, 1, 3, 4 },
		{ 5, 5, 1, 4 },
	},
	c = {
		{ 1, 2, 1 },
		{ 2, 1, 2 },
		{ 1, 2, 1 },
	},
	d = {
		{ 1, 1, 1 },
		{ 3, 1, 3 },
	};
	OutBool(isPrintable(a));
	OutBool(isPrintable(b));
	OutBool(isPrintable(c));
	OutBool(isPrintable(d));
}
