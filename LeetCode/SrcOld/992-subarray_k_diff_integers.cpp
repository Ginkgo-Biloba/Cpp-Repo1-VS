#include "leetcode.hpp"

/* 992. K 个不同整数的子数组

给定一个正整数数组 A，如果 A 的某个子数组中不同整数的个数恰好为 K，则称 A 的这个连续、不一定独立的子数组为好子数组。

（例如，[1,2,3,1,2] 中有 3 个不同的整数：1，2，以及 3。）

返回 A 中好子数组的数目。

示例 1：
输出：A = [1,2,1,2,3], K = 2
输入：7
解释：恰好由 2 个不同整数组成的子数组：[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].

示例 2：
输入：A = [1,2,1,3,4], K = 3
输出：3
解释：恰好由 3 个不同整数组成的子数组：[1,2,1,3], [2,1,3], [1,3,4].

提示：
	1 <= A.length <= 20000
	1 <= A[i] <= A.length
	1 <= K <= A.length
*/

int atMost(vector<int>& A, int K)
{
	int n = static_cast<int>(A.size());
	int h = 0, i = 0, s = 0;
	vector<int> cnt(n + 1);
	for (; i < n; ++i)
	{
		++(cnt[A[i]]);
		if (cnt[A[i]] == 1)
			--K;
		for (; K < 0 && h <= i; ++h)
		{
			--(cnt[A[h]]);
			if (cnt[A[h]] == 0)
				++K;
		}
		s += i - h + 1;
	}
	return s;
}

int subarraysWithKDistinct(vector<int>& A, int K)
{
	return atMost(A, K) - atMost(A, K - 1);
}


int main()
{
	vector<int>
		a = { 1, 2, 1, 2, 3 },
		b = { 1, 2, 1, 3, 4 };
	OutExpr(subarraysWithKDistinct(a, 2), "%d");
	OutExpr(subarraysWithKDistinct(b, 3), "%d");
	OutExpr(subarraysWithKDistinct(b, 1), "%d");
}
