#include "leetcode.hpp"

/* 1723. 完成所有工作的最短时间

给你一个整数数组 jobs ，其中 jobs[i] 是完成第 i 项工作要花费的时间。

请你将这些工作分配给 k 位工人。
所有工作都应该分配给工人，且每项工作只能分配给一位工人。
工人的 工作时间 是完成分配给他们的所有工作花费时间的总和。
请你设计一套最佳的工作分配方案，使工人的 最大工作时间 得以 最小化 。

返回分配方案中尽可能 最小 的 最大工作时间 。

示例 1：
输入：jobs = [3,2,3], k = 3
输出：3
解释：给每位工人分配一项工作，最大工作时间是 3 。

示例 2：
输入：jobs = [1,2,4,7,8], k = 2
输出：11
解释：按下述方式分配工作：
1 号工人：1、2、8（工作时间 = 1 + 2 + 8 = 11）
2 号工人：4、7（工作时间 = 4 + 7 = 11）
最大工作时间是 11 。

提示：
	1 <= k <= jobs.length <= 12
	1 <= jobs[i] <= 10^7
*/

// https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/discuss/1010057/Python-Binary-search-24ms
// 抄的
class Solution
{
	vector<int> A, C;
	int n, k, m;

	bool dfs(int i)
	{
		if (i == n)
			return true;
		for (int j = 0; j < k; ++j)
		{
			if (C[j] >= A[i])
			{
				C[j] -= A[i];
				if (dfs(i + 1))
					return true;
				C[j] += A[i];
			}
			if (C[j] == m)
				break;
		}
		return false;
	}

public:
	int minimumTimeRequired(vector<int>& jobs, int _k)
	{
		A = jobs;
		n = static_cast<int>(A.size());
		k = _k;
		sort(A.begin(), A.end(), std::greater<int>());
		int a = A[0], b = 0;
		for (int i = 0; i < n; ++i)
			b += A[i];
		while (a < b)
		{
			m = (a + b) / 2;
			C.assign(k, m);
			if (dfs(0))
				b = m;
			else
				a = m + 1;
		}
		return a;
	}
};


int main()
{
	vector<int>
		a = { 3, 2, 3 },
		b = { 1, 2, 4, 7, 8 };
	Solution s;
	OutExpr(s.minimumTimeRequired(a, 3), "%d");
	OutExpr(s.minimumTimeRequired(b, 2), "%d");
}
