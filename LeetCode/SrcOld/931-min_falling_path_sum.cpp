#include "leetcode.hpp"

/* 931. 下降路径最小和

给定一个方形整数数组 A，我们想要得到通过 A 的下降路径的最小和。

下降路径可以从第一行中的任何元素开始，并从每一行中选择一个元素。
在下一行选择的元素和当前行所选元素最多相隔一列。

示例：

输入：[[1,2,3],[4,5,6],[7,8,9]]
输出：12
解释：
可能的下降路径有：
	[1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
	[2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
	[3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]
和最小的下降路径是 [1,4,7]，所以答案是 12。

提示：
	1 <= A.length == A[0].length <= 100
	-100 <= A[i][j] <= 100
*/

// seam carving
int minFallingPathSum(vector<vector<int>>& A)
{
	int N = static_cast<int>(A.size());
	for (int h = 1; h < N; ++h)
	{
		int* S = A[h - 1].data();
		int* D = A[h].data();
		D[0] += min(S[0], S[1]);
		for (int w = 1; w < N - 1; ++w)
			D[w] += min(min(S[w - 1], S[w]), S[w + 1]);
		D[N - 1] += min(S[N - 2], S[N - 1]);
	}

	int* ptr = A[N - 1].data();
	for (int w = 1; w < N; ++w)
		ptr[0] = min(ptr[0], ptr[w]);
	return ptr[0];
}


int main()
{
	vector<vector<int>>
		a = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	OutExpr(minFallingPathSum(a), "%d");
}
