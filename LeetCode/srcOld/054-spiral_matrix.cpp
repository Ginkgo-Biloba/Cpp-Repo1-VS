#include "leetcode.hpp"

/* 54. 螺旋矩阵

给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

示例 1:
输入:
[
	[ 1, 2, 3 ],
	[ 4, 5, 6 ],
	[ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]

示例 2:
输入:
[
	[1, 2, 3, 4],
	[5, 6, 7, 8],
	[9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

vector<int> spiralOrder(vector<vector<int>>& M)
{
	vector<int> A;
	if (M.empty())
		return A;
	int rows = static_cast<int>(M.size());
	int cols = static_cast<int>(M[0].size());
	int y1 = 0, y2 = rows - 1;
	int x1 = 0, x2 = cols - 1;
	for (; x1 <= x2 && y1 <= y2;)
	{
		for (int w = x1; w <= x2; ++w)
			A.push_back(M[y1][w]);
		++y1;
		for (int h = y1; h <= y2; ++h)
			A.push_back(M[h][x2]);
		--x2;
		if (x1 > x2 || y1 > y2)
			break;
		for (int w = x2; w >= x1; --w)
			A.push_back(M[y2][w]);
		--y2;
		for (int h = y2; h >= y1; --h)
			A.push_back(M[h][x1]);
		++x1;
	}
	return A;
}


int main()
{

}
