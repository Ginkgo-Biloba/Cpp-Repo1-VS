#include "leetcode.hpp"

/* 304. 二维区域和检索 - 矩阵不可变

给定一个二维矩阵，计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2)。

Range Sum Query 2D
上图子矩阵左上角 (row1, col1) = (2, 1) ，右下角(row2, col2) = (4, 3)，该子矩形内元素的总和为 8。

示例:

给定 matrix =
[
	[3, 0, 1, 4, 2],
	[5, 6, 3, 2, 1],
	[1, 2, 0, 1, 5],
	[4, 1, 0, 1, 7],
	[1, 0, 3, 0, 5],
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12

说明:
	你可以假设矩阵不可变。
	会多次调用 sumRegion 方法。
	你可以假设 row1 ≤ row2 且 col1 ≤ col2。
*/

class NumMatrix
{
	vector<vector<int>> p;

public:
	NumMatrix(vector<vector<int>>& matrix)
	{
		size_t rows, cols = 0;
		rows = matrix.size();
		if (rows > 0)
			cols = matrix[0].size();
		p.resize(rows + 1);
		p[0].resize(cols + 1);
		for (size_t h = 0; h < rows; ++h)
		{
			p[h + 1].resize(cols + 1);
			int cur = 0;
			for (size_t w = 0; w < cols; ++w)
			{
				cur += matrix[h][w];
				p[h + 1][w + 1] = p[h][w + 1] + cur;
			}
		}
	}

	int sumRegion(int h1, int w1, int h2, int w2)
	{
		return p[h2 + 1][w2 + 1] - p[h2 + 1][w1]
			- p[h1][w2 + 1] + p[h1][w1];
	}
};


int main()
{}
