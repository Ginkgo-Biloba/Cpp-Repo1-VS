#include "leetcode.hpp"

/* 1031. 两个非重叠子数组的最大和

给出非负整数数组 A ，返回两个非重叠（连续）子数组中元素的最大和，子数组的长度分别为 L 和 M。
这里需要澄清的是，长为 L 的子数组可以出现在长为 M 的子数组之前或之后。

从形式上看，返回最大的 V，而 V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) 并满足下列条件之一：
	0 <= i < i + L - 1 < j < j + M - 1 < A.length, 或
	0 <= j < j + M - 1 < i < i + L - 1 < A.length.

示例 1：
输入：A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
输出：20
解释：子数组的一种选择中，[9] 长度为 1，[6,5] 长度为 2。

示例 2：
输入：A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
输出：29
解释：子数组的一种选择中，[3,8,1] 长度为 3，[8,9] 长度为 2。

示例 3：
输入：A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
输出：31
解释：子数组的一种选择中，[5,6,0,9] 长度为 4，[0,3,8] 长度为 3。

提示：
	L >= 1
	M >= 1
	L + M <= A.length <= 1000
	0 <= A[i] <= 1000
*/

int sum2(vector<int> const& A, int L, int R)
{
	int len = static_cast<int>(A.size());
	vector<int> buf((len * 2) + 2);
	int *sl = buf.data() + 1, *sr = buf.data() + len + 1;
	int cur = 0;
	--L;
	--R;
	for (int i = 0; i < len; ++i)
	{
		cur += A[i];
		if (i >= L)
		{
			sl[i] = max(cur, sl[i - 1]);
			cur -= A[i - L];
		}
	}
	cur = 0;
	for (int i = len - 1; i >= 0; --i)
	{
		cur += A[i];
		if (i + R < len)
		{
			sr[i] = max(cur, sr[i + 1]);
			cur -= A[i + R];
		}
	}
	cur = INT_MIN;
	for (int i = L; i < len - R - 1; ++i)
		cur = max(cur, sl[i] + sr[i + 1]);
	return cur;
}

int maxSumTwoNoOverlap(vector<int>& A, int L, int M)
{
	int s0 = sum2(A, L, M);
	int s1 = sum2(A, M, L);
	return max(s0, s1);
}

int main()
{
	vector<int>
		a = { 0, 6, 5, 2, 2, 5, 1, 9, 4 },
		b = { 3, 8, 1, 3, 2, 1, 8, 9, 0 },
		c = { 2, 1, 5, 6, 0, 9, 5, 0, 3, 8 };
	OutExpr(maxSumTwoNoOverlap(a, 1, 2), "%d");
	OutExpr(maxSumTwoNoOverlap(b, 3, 2), "%d");
	OutExpr(maxSumTwoNoOverlap(c, 4, 3), "%d");
}
