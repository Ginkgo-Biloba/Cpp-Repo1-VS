#include "leetcode.hpp"

/* 782. 变为棋盘

一个 N x N的 board 仅由 0 和 1 组成。
每次移动，你能任意交换两列或是两行的位置。

输出将这个矩阵变为 “棋盘” 所需的最小移动次数。
“棋盘” 是指任意一格的上下左右四个方向的值均与本身不同的矩阵。
如果不存在可行的变换，输出 -1。

示例:
输入: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
输出: 2
解释:
一种可行的变换方式如下，从左到右：
0110     1010     1010
0110 --> 1010 --> 0101
1001     0101     1010
1001     0101     0101
第一次移动交换了第一列和第二列。
第二次移动交换了第二行和第三行。

输入: board = [[0, 1], [1, 0]]
输出: 0
解释:
注意左上角的格值为0时也是合法的棋盘，如：
01
10
也是合法的棋盘.

输入: board = [[1, 0], [1, 0]]
输出: -1
解释:
任意的变换都不能使这个输入变为合法的棋盘。

提示：
	board 是方阵，且行列数的范围是[2, 30]。
	board[i][j] 将只包含 0或 1。
*/

// https://leetcode.com/problems/transform-to-chessboard/discuss/114847/C%2B%2BJavaPython-Solution-with-Explanation
// 抄的
int movesToChessboard(vector<vector<int>>& B)
{
	int N = static_cast<int>(B.size());
	int rowsum = 0, colsum = 0, rowswap = 0, colswap = 0;

	for (int h = 0; h < N; ++h)
		for (int w = 0; w < N; ++w)
		{
			if (B[0][0] ^ B[h][0] ^ B[0][w] ^ B[h][w])
				return -1;
		}

	for (int h = 0; h < N; ++h)
	{
		rowsum += B[0][h];
		colsum += B[h][0];
		if (B[h][0] == (h & 1)) ++rowswap;
		if (B[0][h] == (h & 1)) ++colswap;
	}

	if ((rowsum != N / 2) && (rowsum != (N + 1) / 2)) return -1;
	if ((colsum != N / 2) && (colsum != (N + 1) / 2)) return -1;

	if (N & 1)
	{
		if (rowswap & 1) rowswap = N - rowswap;
		if (colswap & 1) colswap = N - colswap;
	}
	else
	{
		rowswap = std::min(rowswap, N - rowswap);
		colswap = std::min(colswap, N - colswap);
	}

	return (rowswap + colswap) / 2;
}


int main()
{
	vector<vector<int>>
		n0 = { { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0, 1 } },
		n1 = { { 0, 1 }, { 1, 0 } },
		n2 = { { 1, 0 }, { 1, 0 } };
	OutExpr(movesToChessboard(n0), "%d");
	OutExpr(movesToChessboard(n1), "%d");
	OutExpr(movesToChessboard(n2), "%d");
}
