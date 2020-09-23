#include "leetcode.hpp"

/* 1595. 连通两组点的最小成本

给你两组点，其中第一组中有 size1 个点，第二组中有 size2 个点，且 size1 >= size2 。

任意两点间的连接成本 cost 由大小为 size1 x size2 矩阵给出，其中 cost[i][j] 是第一组中的点 i 和第二组中的点 j 的连接成本。
如果两个组中的每个点都与另一组中的一个或多个点连接，则称这两组点是连通的。
换言之，第一组中的每个点必须至少与第二组中的一个点连接，且第二组中的每个点必须至少与第一组中的一个点连接。

返回连通两组点所需的最小成本。

示例 1：
https://assets.leetcode.com/uploads/2020/09/03/ex1.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/09/20/ex1.jpg
输入：cost = [[15, 96], [36, 2]]
输出：17
解释：连通两组点的最佳方法是：
1--A
2--B
总成本为 17 。

示例 2：
https://assets.leetcode.com/uploads/2020/09/03/ex2.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/09/20/ex2.jpg
输入：cost = [[1, 3, 5], [4, 1, 1], [1, 5, 3]]
输出：4
解释：连通两组点的最佳方法是：
1--A
2--B
2--C
3--A
最小成本为 4 。
请注意，虽然有多个点连接到第一组中的点 2 和第二组中的点 A ，但由于题目并不限制连接点的数目，所以只需要关心最低总成本。

示例 3：
输入：cost = [[2, 5, 1], [3, 4, 7], [8, 1, 2], [6, 2, 4], [3, 8, 8]]
输出：10

提示：
	size1 == cost.length
	size2 == cost[i].length
	1 <= size1, size2 <= 12
	size1 >= size2
	0 <= cost[i][j] <= 100
*/

// 算法是抄的别人的答案
int connectTwoGroups(vector<vector<int>>& A)
{
	int slen = static_cast<int>(A.size());
	int dlen = static_cast<int>(A[0].size());
	int mlen = (1 << dlen);
	vector<int> co(mlen), dp(mlen);
	memset(dp.data(), 0x3f, mlen * sizeof(int));
	dp[0] = 0;
	for (int s = 0; s < slen; ++s)
	{
		dp.swap(co);
		memset(dp.data(), 0x3f, mlen * sizeof(int));
		// 不能 dp[0] = 0 因为左边已经连上的点必须还连着
		for (int d = 0; d < dlen; ++d)
		{
			int a = A[s][d];
			int f = 1 << d;
			for (int m = 0; m < mlen; ++m)
			{
				int i = f | m;
				dp[i] = min(dp[i], co[m] + a);
				// 因为有些先前没有碰到的状态会被更新
				// 比如当前点 s 可以连两条线出去
				co[i] = min(dp[i], co[i]);
			}
		}
	}
	return dp[mlen - 1];
}


int main()
{
	vector<vector<int>>
		a = { { 15, 96 }, { 36, 2 } },
		b = { { 1, 3, 5 }, { 4, 1, 1 }, { 1, 5, 3 } },
		c = { { 2, 5, 1 }, { 3, 4, 7 }, { 8, 1, 2 }, { 6, 2, 4 }, { 3, 8, 8 } };
	OutExpr(connectTwoGroups(a), "%d");
	OutExpr(connectTwoGroups(b), "%d");
	OutExpr(connectTwoGroups(c), "%d");
}
