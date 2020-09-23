#include "leetcode.hpp"

/* 1162. 地图分析

你现在手里有一份大小为 N x N 的『地图』（网格） grid，上面的每个『区域』（单元格）都用 0 和 1 标记好了。其中 0 代表海洋，1 代表陆地，你知道距离陆地区域最远的海洋区域是是哪一个吗？请返回该海洋区域到离它最近的陆地区域的距离。

我们这里说的距离是『曼哈顿距离』（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个区域之间的距离是 |x0 - x1| + |y0 - y1| 。

如果我们的地图上只有陆地或者海洋，请返回 -1。

示例 1：
https://assets.leetcode.com/uploads/2019/05/03/1336_ex1.JPG
输入：[[1,0,1],[0,0,0],[1,0,1]]
输出：2
解释：
海洋区域 (1, 1) 和所有陆地区域之间的距离都达到最大，最大距离为 2。

示例 2：
https://assets.leetcode.com/uploads/2019/05/03/1336_ex2.JPG
输入：[[1,0,0],[0,0,0],[0,0,0]]
输出：4
解释：
海洋区域 (2, 2) 和所有陆地区域之间的距离都达到最大，最大距离为 4。

提示：
	1 <= grid.length == grid[0].length <= 100
	grid[i][j] 不是 0 就是 1。
*/

// 距离变换
int maxDistance(vector<vector<int>>& grid)
{
	int len = static_cast<int>(grid.size());
	int count1 = 0, h, w, dist = 0;
	int *S = nullptr, *U = nullptr;
	for (h = 0; h < len; ++h)
	{
		S = grid[h].data();
		for (w = 0; w < len; ++w)
		{
			count1 += S[w];
			S[w] = S[w] ? 0 : (INT_MAX - 2);
		}
	}
	if (count1 == 0 || count1 == len * len)
		return -1;

#define check(val)      \
	do                    \
	{                     \
		if (S[w] > val + 1) \
			S[w] = val + 1;   \
	} while (0)

	S = grid[0].data();
	for (w = 1; w < len; ++w)
		check(S[w - 1]);
	for (h = 1; h < len; ++h)
	{
		U = grid[h - 1].data();
		S = grid[h].data();
		w = 0;
		check(U[0]);
		for (++w; w < len; ++w)
		{
			check(U[w]);
			check(S[w - 1]);
		}
	}

	S = grid[len - 1].data();
	for (w = len - 2; w >= 0; --w)
		check(S[w + 1]);
	for (h = len - 2; h >= 0; --h)
	{
		U = grid[h + 1].data();
		S = grid[h].data();
		w = len - 1;
		check(U[w]);
		for (--w; w >= 0; --w)
		{
			check(U[w]);
			check(S[w + 1]);
		}
	}

#undef check

	for (h = 0; h < len; ++h)
	{
		S = grid[h].data();
		for (w = 0; w < len; ++w)
			dist = max(dist, S[w]);
	}
	return dist;
}


int main()
{
	vector<vector<int>>
		a = { { 1, 0, 1 }, { 0, 0, 0 }, { 1, 0, 1 } },
		b = { { 1, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
	OutExpr(maxDistance(a), "%d");
	OutExpr(maxDistance(b), "%d");
}
