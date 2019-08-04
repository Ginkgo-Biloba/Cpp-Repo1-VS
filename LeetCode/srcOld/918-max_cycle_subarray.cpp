#include "leetcode.hpp"


int maxSubarraySumCircular(vector<int>& A)
{
	int const len = static_cast<int>(A.size());
	if (len < 2) return A[0];

	int ans, sum = 0;
	int mincur = 0, minsum = A[0];
	int maxcur = 0, maxsum = A[0];
	for (int i = 0; i < len; ++i)
	{
		sum += A[i];
		maxcur += A[i]; mincur += A[i];
		if (maxsum < maxcur) maxsum = maxcur;
		if (maxcur < 0) maxcur = 0;
		if (minsum > mincur) minsum = mincur;
		if (mincur > 0) mincur = 0;
	}

	ans = maxsum;
	if (sum != minsum)
		ans = std::max(ans, sum - minsum);
	printf("maxsum = %d, sum = %d, minsum = %d\n", maxsum, sum, minsum);
	return ans;
}

int main()
{
	vector<int> A = { 1, -2, 3, -2 }; // 3
	int ans = maxSubarraySumCircular(A);
	printf("%1s = %d\n", "maxSubarraySumCircular", ans);
	A = { 5, -3, 5 }; // 10
	ans = maxSubarraySumCircular(A);
	printf("%1s = %d\n", "maxSubarraySumCircular", ans);
	A = { -5, -2, 5, 6, -2, -7, 0, 2, 8 }; // 14
	ans = maxSubarraySumCircular(A);
	printf("%1s = %d\n", "maxSubarraySumCircular", ans);
	A = { 0, 5, 8, -9, 9, -7, 3, -2 }; // 16
	ans = maxSubarraySumCircular(A);
	printf("%1s = %d\n", "maxSubarraySumCircular", ans);
	A = { -2, -3, -1 }; // -1
	ans = maxSubarraySumCircular(A);
	printf("%1s = %d\n", "maxSubarraySumCircular", ans);
	A = { -3, -5, -2, -5, -6 }; // -2
	ans = maxSubarraySumCircular(A);
	printf("%1s = %d\n", "maxSubarraySumCircular", ans);
}
