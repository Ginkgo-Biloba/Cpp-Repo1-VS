#include "leetcode.hpp"

/* 446. 等差数列划分 II - 子序列

如果一个数列至少有三个元素，并且任意两个相邻元素之差相同，则称该数列为等差数列。

例如，以下数列为等差数列:
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
以下数列不是等差数列。
1, 1, 2, 5, 7

数组 A 包含 N 个数，且索引从 0 开始。该数组子序列将划分为整数序列 (P0, P1, ..., Pk)，P 与 Q 是整数且满足 0 ≤ P0 < P1 < ... < Pk < N。
如果序列 A[P0]，A[P1]，...，A[Pk-1]，A[Pk] 是等差的，那么数组 A 的子序列 (P0，P1，…，PK) 称为等差序列。值得注意的是，这意味着 k ≥ 2。
函数要返回数组 A 中所有等差子序列的个数。
输入包含 N 个整数。每个整数都在 -231 和 231-1 之间，另外 0 ≤ N ≤ 1000。保证输出小于 231-1。

示例：
输入：[2, 4, 6, 8, 10]
输出：7
解释：
所有的等差子序列为：
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]
*/

// https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/solution/deng-chai-shu-lie-hua-fen-ii-zi-xu-lie-by-leetcode/
// 抄的
int numberOfArithmeticSlices(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	if (len < 3)
		return 0;
	int ans = 0;
	vector<std::map<int64_t, int>> cnt(len);
	for (int i = 1; i < len; ++i)
		for (int k = 0; k < i; ++k)
		{
			int64_t delta = static_cast<int64_t>(A[i]) - A[k];
			int sum = 0;
			if (cnt[k].find(delta) != cnt[k].end())
				sum = cnt[k][delta];
			cnt[i][delta] += sum + 1;
			ans += sum;
		}
	return ans;
}


int main()
{
	vector<int> A = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 };
	OutExpr(numberOfArithmeticSlices(A), "%d");
}
