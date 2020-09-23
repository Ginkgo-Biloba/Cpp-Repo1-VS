#include "leetcode.hpp"

/* 1014. 最佳观光组合

给定正整数数组 A，A[i] 表示第 i 个观光景点的评分，并且两个景点 i 和 j 之间的距离为 j - i。

一对景点（i < j）组成的观光组合的得分为 A[i] + A[j] + i - j：景点的评分之和减去它们两者之间的距离。

返回一对观光景点能取得的最高分。

示例：
输入：[8,1,5,2,6]
输出：11
解释：i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11

提示：
	2 <= A.length <= 50000
	1 <= A[i] <= 1000
*/


int maxScoreSightseeingPair1(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<int> S;
	int p = 0, sb;

	for (int i = 0; i < len; ++i)
	{
		while (!S.empty())
		{
			sb = S.back();
			p = max(p, A[i] + A[sb] + sb - i);
			// 如果对于后面的来说，当前的不比上一个差
			if (A[i] - sb >= A[sb] - i)
				S.pop_back();
			else
				break;
		}
		if (S.empty())
			S.push_back(i);
	}
	return p;
}

// https://leetcode.com/problems/best-sightseeing-pair/
// 抄的
int maxScoreSightseeingPair(vector<int>& A)
{
	int ans = 0, cur = 0;
	for (int a : A)
	{
		// cur 表示前面最好的，到这里能贡献多少
		ans = max(ans, cur + a);
		// 往后面距离加 1，需要减 1
		cur = max(cur, a) - 1;
	}
	return ans;
}


int main()
{
	vector<int> a = { 8, 1, 5, 2, 6 };
	OutExpr(maxScoreSightseeingPair(a), "%d");
}
