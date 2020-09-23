#include "leetcode.hpp"

/* 867. 转置矩阵 */

vector<vector<int>> transpose(vector<vector<int>>& A)
{
	int rows = (int)(A.size());
	int cols = (int)(A[0].size());
	vector<vector<int>> T(cols);

	for (int w = 0; w < cols; ++w)
	{
		T[w].reserve(rows);
		for (int h = 0; h < rows; ++h)
			T[w].push_back(A[h][w]);
	}
	return T;
}


int main()
{}
