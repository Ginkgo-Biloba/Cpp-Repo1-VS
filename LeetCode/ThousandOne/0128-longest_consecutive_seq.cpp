#include "leetcode.hpp"

/* 128. 最长连续序列

给定一个未排序的整数数组，找出最长连续序列的长度。

要求算法的时间复杂度为 O(n)。

示例:
输入: [100, 4, 200, 1, 3, 2]
输出: 4
解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。
*/

int longestConsecutive(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int ans = 0;
	unordered_set<int> S{ A.begin(), A.end() };
	for (int i = 0; i < len; ++i)
	{
		int cur = A[i];
		if (S.find(cur - 1) != S.end())
			continue;
		for (++cur; S.find(cur) != S.end();)
			++cur;
		ans = max(ans, cur - A[i]);
	}
	return ans;
}


int main()
{
	vector<int> a = { 100, 4, 200, 1, 3, 2 };
	OutExpr(longestConsecutive(a), "%d");
}
