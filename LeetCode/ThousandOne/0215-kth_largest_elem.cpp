#include "leetcode.hpp"

/* 215. 数组中的第K个最大元素

在未排序的数组中找到第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5

示例 2:
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4

说明:
你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。
*/

void sort(int& a, int& b)
{
	int t = a;
	a = min(a, b);
	b = max(b, t);
}

int findKthLargest(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	int a = 0, b, c = len - 1, val;
	k = len - k;
	while (a < c)
	{
		b = (a + c) / 2;
		sort(A[a], A[b]);
		sort(A[a], A[c]);
		sort(A[b], A[c]);
		// pivot 放在最后
		val = A[b];
		A[b] = A[c - 1];
		A[c - 1] = A[c];
		int p = a, q = c - 1;
		while (p < q)
		{
			while (p < q && A[p] <= val) ++p;
			while (p < q && A[q] >= val) --q;
			std::swap(A[p], A[q]);
		}
		A[c] = A[q];
		A[q] = val;
		if (q == k)
			break;
		else if (q < k)
			a = q + 1;
		else
			c = q - 1;
	}
	return A[k];
}


int main()
{
	vector<int>
		a = { 3, 2, 1, 5, 6, 4 },
		b = { 3, 2, 3, 1, 2, 4, 5, 5, 6 };
	OutExpr(findKthLargest(a, 2), "%d");
	OutExpr(findKthLargest(b, 4), "%d");
}
