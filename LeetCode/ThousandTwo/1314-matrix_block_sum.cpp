#include "leetcode.hpp"

/* 1314. 矩阵区域和

给你一个 m * n 的矩阵 mat 和一个整数 K ，请你返回一个矩阵 answer，其中每个 answer[i][j] 是所有满足下述条件的元素 mat[r][c] 的和：
	i - K <= r <= i + K, j - K <= c <= j + K
	(r, c) 在矩阵内。

示例 1：
输入：mat = [[1,2,3],[4,5,6],[7,8,9]], K = 1
输出：[[12,21,16],[27,45,33],[24,39,28]]

示例 2：
输入：mat = [[1,2,3],[4,5,6],[7,8,9]], K = 2
输出：[[45,45,45],[45,45,45],[45,45,45]]

提示：
	m == mat.length
	n == mat[i].length
	1 <= m, n, K <= 100
	1 <= mat[i][j] <= 100
*/

vector<vector<int>> matrixBlockSum(vector<vector<int>>& src, int K)
{
	int rows = static_cast<int>(src.size());
	int cols = static_cast<int>(src[0].size());

	vector<int> integral((rows + 1) * (cols + 1));
	for (int h = 0; h < rows; ++h)
	{
		int* I0 = integral.data() + h * (cols + 1);
		int* I1 = I0 + (cols + 1);
		int* S = src[h].data();
		for (int w = 0; w < cols; ++w)
			I1[w + 1] = I1[w] + I0[w + 1] - I0[w] + S[w];
	}

	vector<vector<int>> dst;
	dst.swap(src);
	for (int h = 0; h < rows; ++h)
	{
		int h0 = max(h - K, 0);
		int h1 = min(h + 1 + K, rows);
		int* I0 = integral.data() + h0 * (cols + 1);
		int* I1 = integral.data() + h1 * (cols + 1);
		int* D = dst[h].data();
		for (int w = 0; w < cols; ++w)
		{
			int w0 = max(w - K, 0);
			int w1 = min(w + 1 + K, cols);
			D[w] = I1[w1] - I1[w0] - I0[w1] + I0[w0];
		}
	}
	return dst;
}


int main()
{}
