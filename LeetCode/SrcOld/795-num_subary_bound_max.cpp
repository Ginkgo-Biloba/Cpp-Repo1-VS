#include "leetcode.hpp"

/* 795. 区间子数组个数

给定一个元素都是正整数的数组A ，正整数 L 以及 R (L <= R)。
求连续、非空且其中最大元素满足大于等于L 小于等于R的子数组个数。

例如 :
输入:
A = [2, 1, 4, 3]
L = 2
R = 3
输出: 3
解释: 满足条件的子数组: [2], [2, 1], [3].

注意:
	L, R  和 A[i] 都是整数，范围在 [0, 10^9]。
	数组 A 的长度范围在[1, 50000]。
*/

// https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/discuss/117616/C%2B%2B-O(n)-less10-lines
// 抄的
int numSubarrayBoundedMax(vector<int>& A, int L, int R)
{
	int len = static_cast<int>(A.size());
	int iL = -1, iR = -1, ans = 0;
	for (int i = 0; i < len; ++i)
	{
		if (A[i] > R) iL = i;
		if (A[i] >= L) iR = i;
		ans += (iR - iL);
	}
	return ans;
}


int main()
{
	vector<int> A = { 2, 1, 4, 3 };
	OutExpr(numSubarrayBoundedMax(A, 2, 3), "%d");
}
