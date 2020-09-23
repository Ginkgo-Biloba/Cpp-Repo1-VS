#include "leetcode.hpp"

/* 891. 子序列宽度之和

给定一个整数数组 A ，考虑 A 的所有非空子序列。

对于任意序列 S ，设 S 的宽度是 S 的最大元素和最小元素的差。

返回 A 的所有子序列的宽度之和。

由于答案可能非常大，请返回答案模 10^9+7。

示例：
输入：[2,1,3]
输出：6
解释：
子序列为 [1]，[2]，[3]，[2,1]，[2,3]，[1,3]，[2,1,3] 。
相应的宽度是 0，0，0，1，1，2，2 。
这些宽度之和是 6 。

提示：
	1 <= A.length <= 20000
	1 <= A[i] <= 20000
*/

// https://leetcode.com/problems/sum-of-subsequence-widths/discuss/161267/C%2B%2BJava1-line-Python-Sort-and-One-Pass
// 抄的
int sumSubseqWidths(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	if (len < 2)
		return 0;

	int64_t const Mod = 1e9 + 7;
	int64_t s = 0, m = 1;
	sort(A.begin(), A.end());
	for (int i = 0; i < len; ++i)
	{
		s = (s + A[i] * m - A[len - 1 - i] * m) % Mod;
		m = (m * 2) % Mod;
	}
	s = (s + Mod) % Mod;
	return static_cast<int>(s);
}

int main()
{
	vector<int> a = { 2, 1, 3 };
	OutExpr(sumSubseqWidths(a), "%d");
}
