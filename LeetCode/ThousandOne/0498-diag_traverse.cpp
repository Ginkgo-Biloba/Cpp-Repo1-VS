#include "leetcode.hpp"

/* 498. 对角线遍历

给定一个含有 M x N 个元素的矩阵（M 行，N 列），请以对角线遍历的顺序返回这个矩阵中的所有元素，对角线遍历如下图所示。

示例:

输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

输出:  [1,2,4,7,5,3,6,8,9]

说明:
		给定矩阵中的元素总数不会超过 100000 。
*/

// https://leetcode.com/problems/diagonal-traverse/discuss/97711/Java-15-lines-without-using-boolean
// 抄的
vector<int> findDiagonalOrder(vector<vector<int>>& m)
{
	vector<int> diag;
	int rows = static_cast<int>(m.size());
	if (rows == 0)
		return diag;
	int cols = static_cast<int>(m[0].size());
	if (cols == 0)
		return diag;
	int h = 0, w = 0;
	int rcstop = rows * cols;

	for (int n = 0; n < rcstop; ++n)
	{
		diag.push_back(m[h][w]);
		// 上移
		if ((h + w) % 2 == 0)
		{
			if (w == cols - 1)
				++h;
			else if (h == 0)
				++w;
			else
			{
				--h;
				++w;
			}
		}
		// 下移
		else
		{
			if (h == rows - 1)
				++w;
			else if (w == 0)
				++h;
			else
			{
				++h;
				--w;
			}
		}
	}

	return diag;
}


int main()
{
	vector<vector<int>> m = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 },
	};
	output(findDiagonalOrder(m), "findDiagonalOrder");
}
