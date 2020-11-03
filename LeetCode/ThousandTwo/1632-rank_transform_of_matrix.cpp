#include "leetcode.hpp"

/* 1632. 矩阵转换后的秩

给你一个 m x n 的矩阵 matrix ，请你返回一个新的矩阵 answer ，其中 answer[row][col] 是 matrix[row][col] 的秩。

每个元素的 秩 是一个整数，表示这个元素相对于其他元素的大小关系，它按照如下规则计算：
	如果一个元素是它所在行和列的最小值，那么它的 秩 为 1。
	如果两个元素 p 和 q 在 同一行 或者 同一列 ，那么：
		如果 p < q ，那么 rank(p) < rank(q)
		如果 p == q ，那么 rank(p) == rank(q)
		如果 p > q ，那么 rank(p) > rank(q)
	秩 需要越 小 越好。

题目保证按照上面规则 answer 数组是唯一的。

示例 1：
https://assets.leetcode.com/uploads/2020/10/18/rank1.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/25/rank1.jpg
输入：matrix = [[1,2],[3,4]]
输出：[[1,2],[2,3]]
解释：
matrix[0][0] 的秩为 1 ，因为它是所在行和列的最小整数。
matrix[0][1] 的秩为 2 ，因为 matrix[0][1] > matrix[0][0] 且 matrix[0][0] 的秩为 1 。
matrix[1][0] 的秩为 2 ，因为 matrix[1][0] > matrix[0][0] 且 matrix[0][0] 的秩为 1 。
matrix[1][1] 的秩为 3 ，因为 matrix[1][1] > matrix[0][1]， matrix[1][1] > matrix[1][0] 且 matrix[0][1] 和 matrix[1][0] 的秩都为 2 。

示例 2：
https://assets.leetcode.com/uploads/2020/10/18/rank2.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/25/rank2.jpg
输入：matrix = [[7,7],[7,7]]
输出：[[1,1],[1,1]]

示例 3：
https://assets.leetcode.com/uploads/2020/10/18/rank3.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/25/rank3.jpg
输入：matrix = [[20,-21,14],[-19,4,19],[22,-47,24],[-19,4,19]]
输出：[[4,2,3],[1,3,4],[5,1,6],[1,3,4]]

示例 4：
https://assets.leetcode.com/uploads/2020/10/18/rank4.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/25/rank4.jpg
输入：matrix = [[7,3,6],[1,4,5],[9,8,2]]
输出：[[5,1,4],[1,2,3],[6,3,1]]

提示：
	m == matrix.length
	n == matrix[i].length
	1 <= m, n <= 500
	-10^9 <= matrix[row][col] <= 10^9
*/

// https://leetcode.com/problems/rank-transform-of-a-matrix/discuss/909142/Python-Union-Find/743552
// 抄的
class Solution
{
public:
	vector<vector<int>> matrixRankTransform(vector<vector<int>>& mat)
	{
		int m = static_cast<int>(mat.size());
		int n = static_cast<int>(mat[0].size());
		map<int, vector<int>> mp;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				mp[mat[i][j]].push_back(i * n + j);

		vector<int> rank(m + n, 0);
		vector<vector<int>> res(m, vector<int>(n));

		for (auto& it : mp)
		{
			vector<int> root(m + n, 0);
			iota(begin(root), end(root), 0);

			auto& v = it.second;
			for (auto& a : v)
			{
				int i = a / n, j = a % n;
				int r1 = find(root, i), r2 = find(root, j + m);
				root[r1] = r2; // make row point to column
				rank[r2] = max(rank[r1], rank[r2]);
			}

			auto rank2 = rank;
			for (auto& a : v)
			{
				int i = a / n, j = a % n;
				int r = find(root, i);
				res[i][j] = rank[r] + 1;
				rank2[i] = rank[r] + 1;
				rank2[j + m] = rank[r] + 1;
			}

			rank.swap(rank2);
		}

		return res;
	}

	int find(vector<int>& root, int x)
	{
		if (root[x] != x)
			root[x] = find(root, root[x]);
		return root[x];
	}
};


int main()
{
	vector<vector<int>>
		a = { { 1, 2 }, { 3, 4 } },
		b = { { 7, 7 }, { 7, 7 } },
		c = { { 20, -21, 14 }, { -19, 4, 19 }, { 22, -47, 24 }, { -19, 4, 19 } },
		d = { { 7, 3, 6 }, { 1, 4, 5 }, { 9, 8, 2 } },
		e = {
			{ -37, -50, -3, 44 },
			{ -37, 46, 13, -32 },
			{ 47, -42, -3, -40 },
			{ -17, -22, -39, 24 },
	},
	f = {
		{ -24, -9, -14, -15, 44, 31, -46, 5, 20, -5, 34 },
		{ 9, -40, -49, -50, 17, 40, 35, 30, -39, 36, -49 },
		{ -18, -43, -40, -5, -30, 9, -28, -41, -6, -47, 12 },
		{ 11, 42, -23, 20, 35, 34, -39, -16, 27, 34, -15 },
		{ 32, 27, -30, 29, -48, 15, -50, -47, -28, -21, 38 },
		{ 45, 48, -1, -18, 9, -4, -13, 10, 9, 8, -41 },
		{ -42, -35, 20, -17, 10, 5, 36, 47, 6, 1, 8 },
		{ 3, -50, -23, 16, 31, 2, -39, 36, -25, -30, 37 },
		{ -48, -41, 18, -31, -48, -1, -42, -3, -8, -29, -2 },
		{ 17, 0, 31, -30, -43, -20, -37, -6, -43, 8, 19 },
		{ 42, 25, 32, 27, -2, 45, 12, -9, 34, 17, 32 },
	};
	Solution s;
	output(s.matrixRankTransform(a), "Rank");
	output(s.matrixRankTransform(b), "Rank");
	output(s.matrixRankTransform(c), "Rank");
	output(s.matrixRankTransform(d), "Rank");
	output(s.matrixRankTransform(e), "Rank");
	output(s.matrixRankTransform(f), "Rank");
}
