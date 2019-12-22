#include "leetcode.hpp"

/*


*/

int smallestRangeI(vector<int>& A, int K)
{
	size_t len = A.size();
	int a = A[0], b = A[0];
	for (size_t i = 1; i < len; ++i)
	{
		a = min(a, A[i]);
		b = max(b, A[i]);
	}
	return max(0, b - a - 2 * K);
}


int main()
{
	vector<int> a = { 3, 1, 2, 4 };
	OutExpr(sumSubarrayMins(a), "%d");
}
