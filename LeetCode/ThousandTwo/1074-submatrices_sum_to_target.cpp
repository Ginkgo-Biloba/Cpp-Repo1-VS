#include "leetcode.hpp"

/* 1074. 元素和为目标值的子矩阵数量

给出矩阵 matrix 和目标值 target，返回元素总和等于目标值的非空子矩阵的数量。

子矩阵 x1, y1, x2, y2 是满足 x1 <= x <= x2 且 y1 <= y <= y2 的所有单元 matrix[x][y] 的集合。

如果 (x1, y1, x2, y2) 和 (x1', y1', x2', y2') 两个子矩阵中部分坐标不同（如：x1 != x1'），那么这两个子矩阵也不同。

示例 1：
输入：matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
输出：4
解释：四个只含 0 的 1x1 子矩阵。

示例 2：
输入：matrix = [[1,-1],[-1,1]], target = 0
输出：5
解释：两个 1x2 子矩阵，加上两个 2x1 子矩阵，再加上一个 2x2 子矩阵。

提示：
	1 <= matrix.length <= 300
	1 <= matrix[0].length <= 300
	-1000 <= matrix[i] <= 1000
	-10^8 <= target <= 10^8
*/

// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/discuss/303750/JavaC%2B%2BPython-Find-the-Subarray-with-Target-Sum
// 抄的
int numSubmatrixSumTarget(vector<vector<int>>& A, int T)
{
	int rows = static_cast<int>(A.size());
	int cols = static_cast<int>(A[0].size());
	int num = 0;

	// 列方向累加
	for (int h = 1; h < rows; ++h)
	{
		for (int w = 0; w < cols; ++w)
			A[h][w] += A[h - 1][w];
	}

	// 行方向滤波
	for (int h = 0; h < rows; ++h)
		for (int i = h; i < rows; ++i)
		{
			unordered_map<int, int> count;
			count[0] = 1;
			int cur = 0;
			for (int w = 0; w < cols; ++w)
			{
				cur += A[i][w];
				if (h > 0)
					cur -= A[h - 1][w];
				auto it = count.find(cur - T);
				if (it != count.end())
					num += it->second;
				count[cur] += 1;
			}
		}

	return num;
}


int main()
{
	vector<vector<int>>
		a = { { 0, 1, 0 }, { 1, 1, 1 }, { 0, 1, 0 } },
		b = { { 1, -1 }, { -1, 1 } };
	OutExpr(numSubmatrixSumTarget(a, 0), "%d");
	OutExpr(numSubmatrixSumTarget(b, 0), "%d");
}
