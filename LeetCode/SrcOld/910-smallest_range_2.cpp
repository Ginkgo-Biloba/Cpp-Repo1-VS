#include "leetcode.hpp"

/* 910. 最小差值 II

给定一个整数数组 A，对于每个整数 A[i]，我们可以选择 x = -K 或是 x = K，并将 x 加到 A[i] 中。

在此过程之后，我们得到一些数组 B。

返回 B 的最大值和 B 的最小值之间可能存在的最小差值。

示例 1：
输入：A = [1], K = 0
输出：0
解释：B = [1]

示例 2：
输入：A = [0,10], K = 2
输出：6
解释：B = [2,8]

示例 3：
输入：A = [1,3,6], K = 3
输出：3
解释：B = [4,6,3]

提示：
	1 <= A.length <= 10000
	0 <= A[i] <= 10000
	0 <= K <= 10000
*/

// 抄的
int smallestRangeII(vector<int>& A, int K)
{
	int n = static_cast<int>(A.size());
	sort(A.begin(), A.end());
	int d = A[n - 1] - A[0];
	for (int i = 0; i < n - 1; ++i)
	{
		int lo = min(A[0] + K, A[i + 1] - K);
		int hi = max(A[i] + K, A[n - 1] - K);
		d = min(d, hi - lo);
	}
	return d;
}

int main()
{
	vector<int>
		a = { 1 },
		b = { 0, 10 },
		c = { 1, 3, 6 },
		d = { 2, 7, 2 };
	OutExpr(smallestRangeII(a, 0), "%d");
	OutExpr(smallestRangeII(b, 2), "%d");
	OutExpr(smallestRangeII(c, 3), "%d");
}
