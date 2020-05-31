#include "leetcode.hpp"

/* 221. 最大正方形

在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。

示例:

输入:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

输出: 4
*/

int maximalSquare(vector<vector<char>>& m)
{
	int rows = static_cast<int>(m.size());
	if (rows == 0) return 0;
	int cols = static_cast<int>(m[0].size());
	int ans = 0;
	vector<int> pre(cols), cur(cols);
	for (int w = 0; w < cols; ++w)
	{
		cur[w] = m[0][w] == '1';
		ans = max(ans, cur[w]);
	}
	for (int h = 1; h < rows; ++h)
	{
		pre.swap(cur);
		cur[0] = m[h][0] == '1';
		for (int w = 1; w < cols; ++w)
			if (m[h][w] == '1')
			{
				cur[w] = 1
					+ min(min(pre[w - 1], pre[w]), cur[w - 1]);
			}
			else
				cur[w] = 0;
		for (int w = 0; w < cols; ++w)
			ans = max(ans, cur[w]);
	}
	return ans * ans;
}


int main()
{}
