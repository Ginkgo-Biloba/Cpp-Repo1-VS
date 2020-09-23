#include "leetcode.hpp"

/* 1329. 将矩阵按对角线排序

给你一个 m * n 的整数矩阵 mat，请你将同一条对角线上的元素（从左上到右下）按升序排序后，返回排好序的矩阵。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/25/1482_example_1_2.png
输入：mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
输出：[[1,1,1,1],[1,2,2,2],[1,2,3,3]]

提示：
	m == mat.length
	n == mat[i].length
	1 <= m, n <= 100
	1 <= mat[i][j] <= 100。
*/


vector<vector<int>> diagonalSort(vector<vector<int>>& M)
{
	int rows = static_cast<int>(M.size());
	int cols = static_cast<int>(M[0].size());
	int len;
	vector<int> A;
	vector<int*> P;
	A.reserve(rows);
	P.reserve(rows);
	for (int d = -cols + 1; d < rows; ++d)
	{
		A.clear();
		P.clear();
		for (int w = 0; w < cols; ++w)
		{
			int h = w + d;
			if (static_cast<unsigned>(h) < static_cast<unsigned>(rows)
				&& static_cast<unsigned>(w) < static_cast<unsigned>(cols))
			{
				A.push_back(M[h][w]);
				P.push_back(&(M[h][w]));
			}
		}
		sort(A.begin(), A.end());
		len = static_cast<int>(A.size());
		for (int i = 0; i < len; ++i)
			*(P[i]) = A[i];
	}
	return M;
}

int main()
{}
