#include "leetcode.hpp"

/* 1815. 得到新鲜甜甜圈的最多组数

有一个甜甜圈商店，每批次都烤 batchSize 个甜甜圈。
这个店铺有个规则，就是在烤一批新的甜甜圈时，之前 所有 甜甜圈都必须已经全部销售完毕。

给你一个整数 batchSize 和一个整数数组 groups ，数组中的每个整数都代表一批前来购买甜甜圈的顾客，其中 groups[i] 表示这一批顾客的人数。
每一位顾客都恰好只要一个甜甜圈。

当有一批顾客来到商店时，他们所有人都必须在下一批顾客来之前购买完甜甜圈。
如果一批顾客中第一位顾客得到的甜甜圈不是上一组剩下的，那么这一组人都会很开心。

你可以随意安排每批顾客到来的顺序。
请你返回在此前提下，最多 有多少组人会感到开心。

示例 1：
输入：batchSize = 3, groups = [1,2,3,4,5,6]
输出：4
解释：你可以将这些批次的顾客顺序安排为 [6,2,4,5,1,3] 。那么第 1，2，4，6 组都会感到开心。

示例 2：
输入：batchSize = 4, groups = [1,3,2,5,2,2,1,6]
输出：4

提示：
	1 <= batchSize <= 9
	1 <= groups.length <= 30
	1 <= groups[i] <= 10^9
*/

// https://leetcode-cn.com/problems/maximum-number-of-groups-getting-fresh-donuts/solution/cji-yi-hua-sou-suo-by-oldyan-658o/
// 抄的
class Solution
{
	union U
	{
		uint64_t a;
		uint8_t c[8];
	};

	unordered_map<uint64_t, int> M;
	int batch;

	// cur 表示目前左边的余数，state 表示剩余顾客的分布
	int dfs(int cur, U state)
	{
		auto it = M.find(state.a);
		if (it != M.end())
			return it->second;
		int ans = 0;
		// 如果还有余数为i的顾客，就尝试令他作为下一波顾客
		for (int i = 1; i < batch; ++i)
			if (state.c[i - 1] > 0)
			{
				state.c[i - 1] = static_cast<uint8_t>(state.c[i - 1] - 1);
				int t = dfs((cur + i) % batch, state);
				state.c[i - 1] = static_cast<uint8_t>(state.c[i - 1] + 1);
				ans = max(ans, cur ? t : t + 1);
			}
		M[state.a] = ans;
		return ans;
	}

public:
	int maxHappyGroups(int batchSize, vector<int>& groups)
	{
		M.clear();
		batch = batchSize;
		U state = { 0 };
		int m = 0;
		for (int i : groups)
		{
			int a = i % batch;
			if (a)
				state.c[a - 1] = static_cast<uint8_t>(state.c[a - 1] + 1);
			else
				m += 1;
		}
		return m += dfs(0, state);
	}
};


int main()
{
	Solution s;
	vector<int>
		a = { 1, 2, 3, 4, 5, 6 },
		b = { 1, 3, 2, 5, 2, 2, 1, 6 };
	OutExpr(s.maxHappyGroups(3, a), "%d");
	OutExpr(s.maxHappyGroups(4, b), "%d");
}
