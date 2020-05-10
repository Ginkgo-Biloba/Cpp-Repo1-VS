#include "leetcode.hpp"

/* 85. 最大矩形

给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。

示例:
输入:
[
	["1","0","1","0","0"],
	["1","0","1","1","1"],
	["1","1","1","1","1"],
	["1","0","0","1","0"]
]
输出: 6
*/

class Solution
{
	vector<int> L, R, S, A;

	// 上一题
	int largestRectangleArea()
	{
		int len = static_cast<int>(A.size());
		assert(len > 0);
		int ans = 0, cur;
		L.resize(len);
		R.resize(len);
		S.clear();
		for (int i = 0; i < len; ++i)
		{
			while (!S.empty() && A[S.back()] >= A[i])
				S.pop_back();
			L[i] = S.empty() ? -1 : S.back();
			S.push_back(i);
		}
		S.clear();
		for (int i = len - 1; i >= 0; --i)
		{
			while (!S.empty() && A[S.back()] >= A[i])
				S.pop_back();
			R[i] = S.empty() ? len : S.back();
			S.push_back(i);
		}
		for (int i = 0; i < len; ++i)
		{
			cur = A[i] * (R[i] - L[i] - 1);
			ans = max(ans, cur);
		}
		return ans;
	}

public:
	int maximalRectangle(vector<vector<char>>& matrix)
	{
		if (matrix.empty())
			return 0;
		int rows = static_cast<int>(matrix.size());
		int cols = static_cast<int>(matrix[0].size());
		int ans = 0, cur;
		A.assign(cols, 0);
		for (int h = 0; h < rows; ++h)
		{
			char const* M = matrix[h].data();
			for (int w = 0; w < cols; ++w)
			{
				if (M[w] == '1')
					A[w] += 1;
				else
					A[w] = 0;
			}
			cur = largestRectangleArea();
			ans = max(ans, cur);
		}
		return ans;
	}
};


int main()
{}
