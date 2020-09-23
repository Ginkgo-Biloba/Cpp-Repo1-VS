#include "leetcode.hpp"

/* 1284. 转化为全零矩阵的最少反转次数

给你一个 m x n 的二进制矩阵 mat。

每一步，你可以选择一个单元格并将它反转（反转表示 0 变 1 ，1 变 0 ）。
如果存在和它相邻的单元格，那么这些相邻的单元格也会被反转。
注：相邻的两个单元格共享同一条边。

请你返回将矩阵 mat 转化为全零矩阵的最少反转次数，如果无法转化为全零矩阵，请返回 -1 。

二进制矩阵的每一个格子要么是 0 要么是 1 。

全零矩阵是所有格子都为 0 的矩阵。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/12/13/matrix.png
输入：mat = [[0,0],[0,1]]
输出：3
解释：一个可能的解是反转 (1, 0)，然后 (0, 1) ，最后是 (1, 1) 。

示例 2：
输入：mat = [[0]]
输出：0
解释：给出的矩阵是全零矩阵，所以你不需要改变它。

示例 3：
输入：mat = [[1,1,1],[1,0,1],[0,0,0]]
输出：6

示例 4：
输入：mat = [[1,0,0],[1,0,0]]
输出：-1
解释：该矩阵无法转变成全零矩阵

提示：
	m == mat.length
	n == mat[0].length
	1 <= m <= 3
	1 <= n <= 3
	mat[i][j] 是 0 或 1 。
*/


// BFS，放到 3 × 3 里面
int minFlips(vector<vector<int>>& mat)
{
	vector<char> visit(1 << 10);
	vector<int> current, nxtloop;
	int neighbour[16][16]; // 拉直后邻域的索引
	int rows = static_cast<int>(mat.size());
	int cols = static_cast<int>(mat[0].size());
	int flag = 0;
	memset(neighbour, 0xff, sizeof(neighbour));
	for (int h = 0; h < rows; ++h)
		for (int w = 0; w < cols; ++w)
		{
			int i = h * 3 + w;
			int n = 0;
			flag |= (mat[h][w] << i);
			neighbour[i][n++] = i;
			if (h > 0)
				neighbour[i][n++] = i - 3;
			if (w > 0)
				neighbour[i][n++] = i - 1;
			flag |= (mat[h][w] << i);
			if (h < rows - 1)
				neighbour[i][n++] = i + 3;
			if (w < cols - 1)
				neighbour[i][n++] = i + 1;
		}
	if (flag == 0)
		return 0;

	current.push_back(flag);
	visit[flag] = 1;
	for (int step = 1; !current.empty(); ++step)
	{
		nxtloop.clear();
		for (int cur : current)
		{
			for (int h = 0; h < rows; ++h)
				for (int w = 0; w < cols; ++w)
				{
					flag = cur;
					int i = h * 3 + w;
					for (int n = 0; neighbour[i][n] >= 0; ++n)
						flag ^= (1 << neighbour[i][n]);
					if (!visit[flag])
					{
						nxtloop.push_back(flag);
						visit[flag] = 1;
					}
				}
			// 外面判断，少些循环分支
			if (visit[0])
				return step;
		}
		nxtloop.swap(current);
	}

	return -1;
}


int main()
{
	vector<vector<int>>
		a = {
			{ 0, 0 },
			{ 0, 1 },
	},
	b = {
		{ 0 },
	},
	c = {
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 0, 0, 0 },
	},
	d = {
		{ 1, 0, 0 },
		{ 1, 0, 0 },
	};
	OutExpr(minFlips(a), "%d");
	OutExpr(minFlips(b), "%d");
	OutExpr(minFlips(c), "%d");
	OutExpr(minFlips(d), "%d");
}
