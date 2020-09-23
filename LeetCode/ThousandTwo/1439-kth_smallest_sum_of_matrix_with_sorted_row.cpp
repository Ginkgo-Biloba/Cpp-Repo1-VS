#include "leetcode.hpp"

/* 1439. 有序矩阵中的第 k 个最小数组和

给你一个 m * n 的矩阵 mat，以及一个整数 k ，矩阵中的每一行都以非递减的顺序排列。

你可以从每一行中选出 1 个元素形成一个数组。
返回所有可能数组中的第 k 个 最小 数组和。

示例 1：
输入：mat = [[1,3,11],[2,4,6]], k = 5
输出：7
解释：从每一行中选出一个元素，前 k 个和最小的数组分别是：
[1,2], [1,4], [3,2], [3,4], [1,6]。其中第 5 个的和是 7 。

示例 2：
输入：mat = [[1,3,11],[2,4,6]], k = 9
输出：17

示例 3：
输入：mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
输出：9
解释：从每一行中选出一个元素，前 k 个和最小的数组分别是：
[1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]。其中第 7 个的和是 9 。

示例 4：
输入：mat = [[1,1,10],[2,2,9]], k = 7
输出：12

提示：
	m == mat.length
	n == mat.length[i]
	1 <= m, n <= 40
	1 <= k <= min(200, n ^ m)
	1 <= mat[i][j] <= 5000
	mat[i] 是一个非递减数组
*/

int kthSmallest1(vector<vector<int>>& mat, int k)
{
	int rows = static_cast<int>(mat.size());
	int cols = static_cast<int>(mat[0].size());
	vector<int> curr, temp;
	curr.swap(mat[0]);
	for (int h = 1; h < rows; ++h)
	{
		temp.clear();
		for (int w = 0; w < cols; ++w)
			for (int val : curr)
				temp.push_back(val + mat[h][w]);
		sort(temp.begin(), temp.end());
		if (temp.size() > static_cast<size_t>(k))
			temp.resize(k);
		temp.swap(curr);
	}
	return curr[k - 1];
}


// 373. Find K Pairs with Smallest Sums
void kSmallestPairs(vector<int>& A, vector<int>& B,
	int k, vector<int>& R)
{
	struct elem
	{
		int s, a, b;
		bool operator<(elem const& e) const
		{
			return s > e.s;
		}
	};

	R.clear();
	int len = static_cast<int>(A.size());
	priority_queue<elem> Q;
	for (int i = 0; i < len; ++i)
		Q.push({ A[i] + B[0], i, 0 });

	len = static_cast<int>(B.size());
	for (; (k > 0) && !(Q.empty()); --k)
	{
		elem e = Q.top();
		Q.pop();
		R.push_back(e.s);
		if (++(e.b) < len)
		{
			e.s = A[e.a] + B[e.b];
			Q.push(e);
		}
	}
}

// https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/discuss/609678/Python-O(k-*-logk-*-len(mat))-with-detailed-explanations-%2B-4-lines-python.
// 抄的
int kthSmallest(vector<vector<int>>& mat, int k)
{
	int rows = static_cast<int>(mat.size());
	vector<int> S, R;
	S.swap(mat[0]);
	for (int h = 1; h < rows; ++h)
	{
		kSmallestPairs(mat[h], S, k, R);
		R.swap(S);
	}
	return S[k - 1];
}


int main()
{
	vector<vector<int>>
		a = { { 1, 3, 11 }, { 2, 4, 6 } },
		b = { { 1, 3, 11 }, { 2, 4, 6 } },
		c = { { 1, 10, 10 }, { 1, 4, 5 }, { 2, 3, 6 } },
		d = { { 1, 1, 10 }, { 2, 2, 9 } };
	OutExpr(kthSmallest(a, 5), "%d");
	OutExpr(kthSmallest(b, 9), "%d");
	OutExpr(kthSmallest(c, 7), "%d");
	OutExpr(kthSmallest(d, 7), "%d");
}
