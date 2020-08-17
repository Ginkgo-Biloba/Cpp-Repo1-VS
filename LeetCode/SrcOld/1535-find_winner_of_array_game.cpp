#include "leetcode.hpp"

/*


*/

int getWinner(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	int xval = -1, cmp = len;
	vector<int> M;
	for (int i = 0; i < len; ++i)
		xval = max(xval, A[i]);
	M.resize(xval + 1);
	for (int p = 1; (--cmp) && (p < len); ++p)
	{
		if (A[0] < A[p])
			A[0] = A[p];
		if (++(M[A[0]]) >= k)
			return A[0];
	}
	return xval;
}

int main()
{
	vector<int>
		a = { 2, 1, 3, 5, 4, 6, 7 },
		b = { 3, 2, 1 },
		c = { 1, 9, 8, 2, 3, 7, 6, 4, 5 },
		d = { 1, 11, 22, 33, 44, 55, 66, 77, 88, 99 },
		e = { 7, 2, 3, 14 };
	OutExpr(getWinner(a, 2), "%d");
	OutExpr(getWinner(b, 10), "%d");
	OutExpr(getWinner(c, 7), "%d");
	OutExpr(getWinner(d, 1000000000), "%d");
	OutExpr(getWinner(e, 3), "%d");
}
