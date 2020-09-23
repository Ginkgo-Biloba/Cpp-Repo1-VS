#include "leetcode.hpp"

/* 48. 旋转图像

给定一个 n × n 的二维矩阵表示一个图像。

将图像顺时针旋转 90 度。

说明：
你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。
请不要使用另一个矩阵来旋转图像。

示例 1:

给定 matrix =
[
	[1,2,3],
	[4,5,6],
	[7,8,9]
],

原地旋转输入矩阵，使其变为:
[
	[7,4,1],
	[8,5,2],
	[9,6,3]
]

示例 2:

给定 matrix =
[
	[ 5, 1, 9,11],
	[ 2, 4, 8,10],
	[13, 3, 6, 7],
	[15,14,12,16]
],

原地旋转输入矩阵，使其变为:
[
	[15,13, 2, 5],
	[14, 3, 4, 1],
	[12, 6, 8, 9],
	[16, 7,10,11]
]
*/

void rotate_Org(vector<vector<int>>& M)
{
	int n = static_cast<int>(M.size());
	int n2 = n / 2;
	// 从外到里，一圈圈旋转
	// (r, c) -> (c, i) -> (i, k) -> (k, r) -> (r, c)
	for (int h = 0; h < n2; h++)
	{
		int i = n - 1 - h;
		for (int w = h; w < i; w++)
		{
			int k = n - 1 - w;
			int val = M[h][w];
			M[h][w] = M[k][h];
			M[k][h] = M[i][k];
			M[i][k] = M[w][i];
			M[w][i] = val;
		}
	}
}

void rotate(vector<vector<int>>& M)
{
	int n = static_cast<int>(M.size());
	// 顺时针旋转，等于先转置再左右翻转
	for (int h = 0; h < n; ++h)
		for (int w = h + 1; w < n; ++w)
		{
			int val = M[h][w];
			M[h][w] = M[w][h];
			M[w][h] = val;
		}
	for (int h = 0; h < n; ++h)
	{
		int* S = M[h].data();
		int p = 0, q = n - 1;
		for (; p < q; ++p, --q)
		{
			int t = S[p];
			S[p] = S[q];
			S[q] = t;
		}
	}
}

int main()
{}
