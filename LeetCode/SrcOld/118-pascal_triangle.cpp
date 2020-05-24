#include "leetcode.hpp"

/* 118. 杨辉三角

给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。

https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif
在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:
输入: 5
输出:
> [
>      [1],
>     [1,1],
>    [1,2,1],
>   [1,3,3,1],
>  [1,4,6,4,1]
> ]
*/

vector<vector<int>> generate(int numRows)
{
	vector<vector<int>> R;
	vector<int> r;
	if (numRows == 0)
		return R;
	for (int h = 0; h < numRows; ++h)
	{
		int cur = 1;
		r.push_back(cur);
		if (h > 0)
		{
			int* ptr = R[h - 1].data();
			for (int w = 0; w < h - 1; ++w)
				r.push_back(ptr[w] + ptr[w + 1]);
			r.push_back(1);
		}
		R.push_back(move(r));
	}
	return R;
}


int main()
{
	output(generate(10), "Pascal's Triangle");
}
