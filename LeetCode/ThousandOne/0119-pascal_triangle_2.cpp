#include "leetcode.hpp"

/* 119. 杨辉三角 II

给定一个非负索引 k，其中 k ≤ 33，返回杨辉三角的第 k 行。

https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif
在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:
输入: 3
输出: [1,3,3,1]

进阶：
你可以优化你的算法到 O(k) 空间复杂度吗？
*/

vector<int> getRow(int rowIndex)
{
	vector<int> A, B;
	A.reserve(rowIndex + 1);
	B.reserve(rowIndex + 1);
	for (int h = -2; h < rowIndex; ++h)
	{
		B.assign(1, 1);
		if (h > -1)
		{
			int* ptr = A.data();
			for (int w = 0; w < h; ++w)
				B.push_back(ptr[w] + ptr[w + 1]);
			B.push_back(1);
		}
		B.swap(A);
	}
	return A;
}


int main()
{
	output(getRow(3), "Pascal's Triangle II");
}
