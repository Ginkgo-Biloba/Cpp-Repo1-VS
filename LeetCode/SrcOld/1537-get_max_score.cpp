#include "leetcode.hpp"

/*


*/

// 赛后抄的第一名的，第一名改版。。。
int maxSum0(vector<int>& nums1, vector<int>& nums2)
{
	int64_t const mod = 1e9 + 7;
	int64_t a = 0, b = 0;
	map<int, int> M;
	for (int i : nums1) M[i] += 1;
	for (int i : nums2) M[i] += 2;
	for (auto const& kv : M)
	{
		if (kv.second == 1) a += kv.first;
		if (kv.second == 2) b += kv.first;
		if (kv.second == 3) a = b = max(a, b) + kv.first;
	}
	return static_cast<int>(max(a, b) % mod);
}

// https://leetcode.com/problems/get-the-maximum-score/discuss/767987/JavaC++Python-Two-Pointers-O(1)-Space/639229
// 抄的
int maxSum(vector<int>& A, vector<int>& B)
{
	int64_t const mod = 1e9 + 7;
	int64_t a = 0, b = 0;
	int p = 0, q = 0;
	int m = static_cast<int>(A.size());
	int n = static_cast<int>(B.size());
	while (p < m && q < n)
	{
		if (A[p] < B[q])
		{
			a += A[p];
			++p;
		}
		else if (A[p] > B[q])
		{
			b += B[q];
			++q;
		}
		else
		{
			a = b = max(a, b) + A[p];
			++p;
			++q;
		}
	}
	for (; p < m; ++p) a += A[p];
	for (; q < n; ++q) b += B[q];
	a = b = max(a, b) % mod;
	return static_cast<int>(a);
}


int main()
{
	vector<int>
		a = { 2, 4, 5, 8, 10 },
		b = { 4, 6, 8, 9 },
		c = { 1, 3, 5, 7, 9 },
		d = { 3, 5, 100 },
		e = { 1, 2, 3, 4, 5 },
		f = { 6, 7, 8, 9, 10 },
		g = { 1, 4, 5, 8, 9, 11, 19 },
		h = { 2, 3, 4, 11, 12 };
	OutExpr(maxSum(a, b), "%d");
	OutExpr(maxSum(c, d), "%d");
	OutExpr(maxSum(e, f), "%d");
	OutExpr(maxSum(g, h), "%d");
}
