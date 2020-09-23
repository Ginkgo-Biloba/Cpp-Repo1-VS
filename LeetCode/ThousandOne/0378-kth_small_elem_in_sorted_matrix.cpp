#include "leetcode.hpp"

/* 378. 有序矩阵中第K小的元素

给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第k小的元素。
请注意，它是排序后的第k小元素，而不是第k个元素。

示例:

matrix = [
[ 1,  5,  9],
[10, 11, 13],
[12, 13, 15]
],
k = 8,

返回 13。

说明:
你可以假设 k 的值永远是有效的, 1 ≤ k ≤ n2 。
*/

// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85173/Share-my-thoughts-and-Clean-Java-Code
// 抄的，原理就是和 373 一样

struct Elem
{
	int y, x;
	int v;

	Elem(int _y, int _x, int _v) : y(_y), x(_x), v(_v) {}

	Elem(Elem const&) = default;

	bool operator <(Elem const& rhs) const
	{
		return v > rhs.v;
	}
};

int kthSmallest(vector<vector<int>>& mat, int k)
{
	int const N = static_cast<int>(mat.size());
	std::priority_queue<Elem> q;
	Elem e(0, 0, mat[0][0]);

	for (int i = 0; i < N; ++i)
		q.emplace(0, i, mat[0][i]);

	while (--k)
	{
		e = q.top();
		q.pop();
		++(e.y);
		if (e.y < N)
		{
			e.v = mat[e.y][e.x];
			q.emplace(e);
		}
	}

	e = q.top();
	return e.v;
}


int main()
{
	vector<vector<int>> nums =
	{
		{ 1, 5, 9 },
		{ 10, 11, 13 },
		{ 12, 13, 15 }
	};
	OutExpr(kthSmallest(nums, 8), "%d");
}
