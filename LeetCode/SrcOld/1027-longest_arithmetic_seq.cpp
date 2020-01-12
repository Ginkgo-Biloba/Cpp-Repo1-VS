#include "leetcode.hpp"

/* 1027. 最长等差数列

给定一个整数数组 A，返回 A 中最长等差子序列的长度。

回想一下，A 的子序列是列表 A[i_1], A[i_2], ..., A[i_k] 其中 0 <= i_1 < i_2 < ... < i_k <= A.length - 1。
并且如果 B[i+1] - B[i]( 0 <= i < B.length - 1) 的值都相同，那么序列 B 是等差的。

示例 1：

输入：[3,6,9,12]
输出：4
解释：
整个数组是公差为 3 的等差数列。

示例 2：
输入：[9,4,7,2,10]
输出：3
解释：
最长的等差子序列是 [4,7,10]。

示例 3：
输入：[20,1,15,3,10,5,8]
输出：4
解释：
最长的等差子序列是 [20,15,10,5]。

提示：
	2 <= A.length <= 2000
	0 <= A[i] <= 10000
*/


int longestArithSeqLength(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int ans = 0;
	// 末尾索引，等差
	vector<std::map<int, int>> M(len);
	for (int k = 1; k < len; ++k)
		for (int i = 0; i < k; ++i)
		{
			int d = A[k] - A[i];
			auto it = M[i].find(d);
			if (it == M[i].end())
				M[k].emplace(d, 2);
			// 不需要 max，因为如果前面可以
			// 后面有相同的肯定也可以，只会长不会短
			else
				M[k][d] = it->second + 1;
			ans = max(ans, M[k][d]);
		}
	return ans;
}


int main()
{
	vector<int>
		a = { 3, 6, 9, 12 },
		b = { 9, 4, 7, 2, 10 },
		c = { 20, 1, 15, 3, 10, 5, 8 },
		d = { 12, 28, 13, 6, 34, 36, 53, 24, 29, 2, 23, 0, 22, 25, 53, 34, 23, 50, 35, 43, 53, 11, 48, 56, 44, 53, 31, 6, 31, 57, 46, 6, 17, 42, 48, 28, 5, 24, 0, 14, 43, 12, 21, 6, 30, 37, 16, 56, 19, 45, 51, 10, 22, 38, 39, 23, 8, 29, 60, 18 };
	OutExpr(longestArithSeqLength(a), "%d");
	OutExpr(longestArithSeqLength(b), "%d");
	OutExpr(longestArithSeqLength(c), "%d");
	OutExpr(longestArithSeqLength(d), "%d");
}
