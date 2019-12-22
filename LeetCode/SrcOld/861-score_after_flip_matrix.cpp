#include "leetcode.hpp"

/* 861. 翻转矩阵后的得分

有一个二维矩阵 A 其中每个元素的值为 0 或 1 。

移动是指选择任一行或列，并转换该行或列中的每一个值：将所有 0 都更改为 1，将所有 1 都更改为 0。

在做出任意次数的移动后，将该矩阵的每一行都按照二进制数来解释，矩阵的得分就是这些数字的总和。

返回尽可能高的分数。

示例：
输入：[[0,0,1,1],[1,0,1,0],[1,1,0,0]]
输出：39
解释：
转换为 [[1,1,1,1],[1,0,0,1],[1,1,1,1]]
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39

提示：
	1 <= A.length <= 20
	1 <= A[0].length <= 20
	A[i][j] 是 0 或 1
*/

// https://leetcode.com/problems/score-after-flipping-matrix/discuss/143722/C%2B%2BJavaPython-Easy-and-Concise
// 抄的
int matrixScore(vector<vector<int>>& A)
{
	int rows = static_cast<int>(A.size());
	int cols = static_cast<int>(A[0].size());
	// 第一列必须翻转到 1
	int sum = (1 << (cols - 1)) * rows;
	for (int w = 1; w < cols; ++w)
	{
		int cur = 0;
		for (int h = 0; h < rows; ++h)
			cur += (A[h][w] == A[h][0]);
		// 这一列翻转还是不翻转
		cur = std::max(cur, rows - cur);
		sum += (1 << (cols - 1 - w)) * cur;
	}
	return sum;
}


int main()
{
	vector<vector<int>>
		a = { { 0, 0, 1, 1 }, { 1, 0, 1, 0 }, { 1, 1, 0, 0 } };
	OutExpr(matrixScore(a), "%d");
}
