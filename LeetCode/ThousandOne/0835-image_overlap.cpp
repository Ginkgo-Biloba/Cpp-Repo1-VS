#include "leetcode.hpp"

/* 835. 图像重叠

给出两个图像 A 和 B ，A 和 B 为大小相同的二维正方形矩阵。（并且为二进制矩阵，只包含0和1）。

我们转换其中一个图像，向左，右，上，或下滑动任何数量的单位，并把它放在另一个图像的上面。
之后，该转换的重叠是指两个图像都具有 1 的位置的数目。

（请注意，转换不包括向任何方向旋转。）

最大可能的重叠是什么？

示例 1:

输入：
A = [[1,1,0],
		 [0,1,0],
		 [0,1,0]]
B = [[0,0,0],
		 [0,1,1],
		 [0,0,1]]
输出：3
解释: 将 A 向右移动一个单位，然后向下移动一个单位。

注意:
	1 <= A.length = A[0].length = B.length = B[0].length <= 30
	0 <= A[i][j], B[i][j] <= 1
*/

// https://leetcode-cn.com/problems/image-overlap/solution/-dui-ahe-bju-you-1de-wei-zhi-ju-chi-ji-shu-by-hare/
// 抄的
int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B)
{
	int N = static_cast<int>(A.size());
	unordered_map<int, int> cnt;
	vector<int> flatA, flatB;

	for (int h = 0; h < N; ++h)
		for (int w = 0; w < N; ++w)
		{
			// 要比 2*N-1 大
			int i = h * 64 + w;
			if (A[h][w])
				flatA.push_back(i);
			if (B[h][w])
				flatB.push_back(i);
		}

	for (int a : flatA)
		for (int b : flatB)
			++(cnt[a - b]);

	N = 0;
	for (auto const& kv : cnt)
		N = std::max(N, kv.second);
	return N;
}


int main()
{
	vector<vector<int>>
		A0 = {
			{ 1, 1, 0 },
			{ 0, 1, 0 },
			{ 0, 1, 0 },
	},
	B0 = {
		{ 0, 0, 0 },
		{ 0, 1, 1 },
		{ 0, 0, 1 },
	};
	OutExpr(largestOverlap(A0, B0), "%d");
}
