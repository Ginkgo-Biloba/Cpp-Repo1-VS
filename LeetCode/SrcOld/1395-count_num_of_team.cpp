#include "leetcode.hpp"

/* 1395. 统计作战单位数

n 名士兵站成一排。每个士兵都有一个 独一无二 的评分 rating。

每 3 个士兵可以组成一个作战单位，分组规则如下：
	从队伍中选出下标分别为 i、j、k 的 3 名士兵，他们的评分分别为 rating[i]、rating[j]、rating[k]
	作战单位需满足：rating[i] < rating[j] < rating[k] 或者 rating[i] > rating[j] > rating[k] ，其中  0 <= i < j < k < n

请你返回按上述条件可以组建的作战单位数量。
每个士兵都可以是多个作战单位的一部分。

示例 1：
输入：rating = [2,5,3,4,1]
输出：3
解释：我们可以组建三个作战单位 (2,3,4)、(5,4,1)、(5,3,1) 。

示例 2：
输入：rating = [2,1,3]
输出：0
解释：根据题目条件，我们无法组建作战单位。

示例 3：
输入：rating = [1,2,3,4]
输出：4

提示：
	n == rating.length
	1 <= n <= 200
	1 <= rating[i] <= 10^5
*/

int numTeams(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<int> gt(len), lt(len);
	for (int i = 1; i < len; ++i)
		for (int k = 0; k < i; ++k)
		{
			if (A[i] > A[k])
				++(gt[i]);
			else if (A[i] < A[k])
				++(lt[i]);
		}

	int sum = 0;
	for (int i = 2; i < len; ++i)
		for (int h = 1; h < i; ++h)
		{
			if (A[i] > A[h])
				sum += gt[h];
			else if (A[i] < A[h])
				sum += lt[h];
		}
	return sum;
}


int main()
{
	vector<int>
		a = { 2, 5, 3, 4, 1 },
		b = { 2, 1, 3 },
		c = { 1, 2, 3, 4 };
	OutExpr(numTeams(a), "%d");
	OutExpr(numTeams(b), "%d");
	OutExpr(numTeams(c), "%d");
}
