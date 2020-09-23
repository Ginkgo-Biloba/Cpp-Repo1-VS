#include "leetcode.hpp"

/* 59. 螺旋矩阵 II

给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

示例:

输入: 3
输出:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

vector<vector<int>> generateMatrix(int n)
{
	vector<vector<int>> M(n);
	for (int h = 0; h < n; ++h)
		M[h].resize(n);
	int cur = 0;
	int y1 = 0, y2 = n - 1;
	int x1 = 0, x2 = n - 1;
	for (; x1 <= x2 && y1 <= y2;)
	{
		for (int w = x1; w <= x2; ++w)
			M[y1][w] = (++cur);
		++y1;
		for (int h = y1; h <= y2; ++h)
			M[h][x2] = (++cur);
		--x2;
		if (x1 > x2 || y1 > y2)
			break;
		for (int w = x2; w >= x1; --w)
			M[y2][w] = (++cur);
		--y2;
		for (int h = y2; h >= y1; --h)
			M[h][x1] = (++cur);
		++x1;
	}
	return M;
}


int main()
{
	output(generateMatrix(1), "Spiral Matrix II");
}
