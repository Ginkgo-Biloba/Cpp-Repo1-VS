#include "leetcode.hpp"

/* 879. 盈利计划

帮派里有 G 名成员，他们可能犯下各种各样的罪行。

第 i 种犯罪会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与。

让我们把这些犯罪的任何子集称为盈利计划，该计划至少产生 P 的利润。

有多少种方案可以选择？因为答案很大，所以返回它模 10^9 + 7 的值。

示例 1：
输入：G = 5, P = 3, group = [2,2], profit = [2,3]
输出：2
解释：
至少产生 3 的利润，该帮派可以犯下罪 0 和罪 1 ，或仅犯下罪 1 。
总的来说，有两种方案。

示例 2:
输入：G = 10, P = 5, group = [2,3,5], profit = [6,7,8]
输出：7
解释：
至少产生 5 的利润，只要他们犯其中一种罪就行，所以该帮派可以犯下任何罪行 。
有 7 种可能的计划：(0)，(1)，(2)，(0,1)，(0,2)，(1,2)，以及 (0,1,2) 。

提示：
	1 <= G <= 100
	0 <= P <= 100
	1 <= group[i] <= 100
	0 <= profit[i] <= 100
	1 <= group.length = profit.length <= 100
*/

class Solution
{
	static int const Mod = 1e9 + 7;
	static int const DSize = 101;
	vector<int> group, profit;
	vector<int> buf;

	int at(int i, int j, int k)
	{
		return (i * DSize + j) * DSize + k;
	}

	// i 搞到哪一个
	// j 还有多少人
	// k 还需要多少钱
	int DP(int i, int j, int k)
	{
		k = std::max(0, k);
		if (j < 0)
			return 0;

		if (i == (int)(group.size()))
			return (j >= 0 && k == 0);

		int ib = at(i, j, k);
		if (buf[ib] != -1)
			return buf[ib];

		int d1 = DP(i + 1, j - group[i], k - profit[i]);
		int d2 = DP(i + 1, j, k);
		int ds = (d1 + d2) % Mod;
		buf[ib] = ds;
		return ds;
	}

public:
	int profitableSchemes(int G, int P, vector<int>& _group, vector<int>& _profit)
	{
		group.swap(_group);
		profit.swap(_profit);
		buf.resize(DSize * DSize * DSize);
		memset(buf.data(), 0xff, DSize * DSize * DSize * sizeof(buf[0]));
		int d = DP(0, G, P);
		return d;
	}
};

// https://leetcode.com/problems/profitable-schemes/discuss/154617/C%2B%2BJavaPython-DP
// 抄的
int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit)
{
	int const Mod = 1e9 + 7;
	int len = static_cast<int>(group.size());
	int sum = 0;
	// dp[p][g] 表示以 p 利润、正好 g 成员能搞到的方案数量
	vector<int> dp((P + 1) * (G + 1));
	auto at = [G](int p, int g) { return p * (G + 1) + g; };
	dp[at(0, 0)] = 1;

	for (int k = 0; k < len; ++k)
	{
		int g = group[k], p = profit[k];
		for (int i = P; i >= 0; --i)
		{
			int ip = std::min(i + p, P);
			for (int j = G; j >= g; --j)
				dp[at(ip, j)] = (dp[at(ip, j)] + dp[at(i, j - g)]) % Mod;
		}
	}
	for (int i = 0; i <= G; ++i)
		sum = (sum + dp[at(P, i)]) % Mod;
	return sum;
}


int main()
{
	vector<int>
		g0 = { 2, 2 },
		p0 = { 2, 3 },
		g1 = { 2, 3, 5 },
		p1 = { 6, 7, 8 },
		g2 = { 8, 8, 7, 4, 3, 1, 1, 6, 11, 3, 1, 7, 6, 9, 9, 1, 8, 9, 3, 10, 10, 8, 7, 6, 9, 10, 6, 2, 2, 6, 9, 7, 5, 6, 2, 1, 2, 10, 11, 6, 8, 9, 9, 8, 11, 6, 2, 2, 4, 5, 1, 2, 1, 11, 3, 2, 11, 7, 11, 4, 5, 7, 6, 9, 6, 7, 10, 10, 9, 10, 10, 8, 8, 6, 9, 8, 5, 1, 2, 5, 10, 1, 4, 2, 1, 5, 1, 3, 6, 6, 10, 6, 2, 3, 2, 1, 9, 6, 6, 4 },
		p2 = { 23, 36, 94, 35, 73, 7, 65, 25, 22, 4, 62, 62, 12, 18, 89, 62, 2, 66, 85, 94, 73, 31, 56, 95, 71, 91, 53, 75, 100, 47, 68, 4, 64, 52, 97, 8, 52, 32, 98, 64, 2, 64, 33, 21, 52, 44, 41, 50, 59, 40, 48, 47, 39, 9, 100, 1, 43, 94, 63, 23, 21, 92, 36, 69, 100, 8, 75, 16, 79, 98, 72, 83, 70, 11, 3, 41, 91, 18, 17, 76, 71, 58, 71, 62, 34, 49, 58, 59, 90, 84, 12, 43, 27, 60, 47, 89, 31, 14, 11, 15 };
	Solution s;
	OutExpr(profitableSchemes(5, 3, g0, p0), "%d");
	OutExpr(profitableSchemes(10, 5, g1, p1), "%d");
	OutExpr(profitableSchemes(10, 100, g2, p2), "%d");
}
