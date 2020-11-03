﻿#include "leetcode.hpp"

/* 1621. 大小为 K 的不重叠线段的数目

给你一维空间的 n 个点，其中第 i 个点（编号从 0 到 n-1）位于 x = i 处，请你找到 恰好 k 个不重叠 线段且每个线段至少覆盖两个点的方案数。
线段的两个端点必须都是 整数坐标 。
这 k 个线段不需要全部覆盖全部 n 个点，且它们的端点 可以 重合。

请你返回 k 个不重叠线段的方案数。
由于答案可能很大，请将结果对 10^9 + 7 取余 后返回。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/17/ex1.png
输入：n = 4, k = 2
输出：5
解释：
如图所示，两个线段分别用红色和蓝色标出。
上图展示了 5 种不同的方案 {(0,2),(2,3)}，{(0,1),(1,3)}，{(0,1),(2,3)}，{(1,2),(2,3)}，{(0,1),(1,2)} 。

示例 2：
输入：n = 3, k = 1
输出：3
解释：总共有 3 种不同的方案 {(0,1)}, {(0,2)}, {(1,2)} 。

示例 3：
输入：n = 30, k = 7
输出：796297179
解释：画 7 条线段的总方案数为 3796297200 种。将这个数对 109 + 7 取余得到 796297179 。

示例 4：
输入：n = 5, k = 3
输出：7

示例 5：
输入：n = 3, k = 2
输出：1

提示：
	2 <= n <= 1000
	1 <= k <= n-1
*/

// https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/discuss/898830/Python-O(N)-Solution-with-Prove
// 抄的
enum LeeCodeKonst
{
	len = 2000,
	mod = static_cast<int>(1e9 + 7),
};
static vector<array<int, len>> C;

class Solution
{
public:
	Solution()
	{
		if (C.size() == len)
			return;
		C.resize(len);
		memset(C.data(), 0, sizeof(C[0]) * len);
		C[0][0] = 1;
		for (int n = 1; n < len; ++n)
		{
			C[n][0] = 1;
			for (int k = 1; k <= n; ++k)
				C[n][k] = (C[n - 1][k] + C[n - 1][k - 1]) % mod;
		}
	}

public:
	int numberOfSets(int n, int k)
	{
		return C[n + k - 1][2 * k];
	}
};


int main()
{
	Solution s;
	OutExpr(s.numberOfSets(4, 2), "%d");
	OutExpr(s.numberOfSets(3, 1), "%d");
	OutExpr(s.numberOfSets(30, 7), "%d");
	OutExpr(s.numberOfSets(5, 3), "%d");
	OutExpr(s.numberOfSets(3, 2), "%d");
}
