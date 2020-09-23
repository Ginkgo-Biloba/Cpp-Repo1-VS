#include "leetcode.hpp"

/* 718. 最长重复子数组

给两个整数数组 A 和 B，返回两个数组中公共的、长度最长的子数组的长度。

示例 1:
输入:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
输出: 3
解释:
长度最长的公共子数组是 [3, 2, 1]。

说明:
	1 <= len(A), len(B) <= 1000
	0 <= A[i], B[i] < 100
*/

int findLength(vector<int>& A, vector<int>& B)
{
	size_t na = A.size(), nb = B.size();
	vector<int> pre(nb + 1), cur(nb + 1);
	int maxlen = 0, cc;
	for (size_t ia = 1; ia <= na; ++ia)
	{
		cc = A[ia - 1];
		pre.swap(cur);
		for (size_t ib = 1; ib <= nb; ++ib)
		{
			if (cc == B[ib - 1])
			{
				cur[ib] = pre[ib - 1] + 1;
				maxlen = std::max(maxlen, cur[ib]);
			}
			else
				cur[ib] = 0;
		}
	}
	return maxlen;
}


int main()
{
	vector<int> A = { 1, 2, 3, 2, 1 };
	vector<int> B = { 3, 2, 1, 4, 7 };
	OutExpr(findLength(A, B), "%d");
	A = { 0, 0, 0, 0, 1 };
	B = { 1, 0, 0, 0, 0 };
	OutExpr(findLength(A, B), "%d");
}
