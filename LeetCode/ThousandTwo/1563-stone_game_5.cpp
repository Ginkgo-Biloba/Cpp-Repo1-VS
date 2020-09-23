#include "leetcode.hpp"

/* 1563. 石子游戏 V

几块石子 排成一行 ，每块石子都有一个关联值，关联值为整数，由数组 stoneValue 给出。

游戏中的每一轮：Alice 会将这行石子分成两个 非空行（即，左侧行和右侧行）；Bob 负责计算每一行的值，即此行中所有石子的值的总和。
Bob 会丢弃值最大的行，Alice 的得分为剩下那行的值（每轮累加）。
如果两行的值相等，Bob 让 Alice 决定丢弃哪一行。
下一轮从剩下的那一行开始。

只剩下一块石子 时，游戏结束。
Alice 的分数最初为 0 。

返回 Alice 能够获得的最大分数 。

示例 1：
输入：stoneValue = [6,2,3,4,5,5]
输出：18
解释：在第一轮中，Alice 将行划分为 [6，2，3]，[4，5，5] 。
左行的值是 11 ，右行的值是 14 。Bob 丢弃了右行，Alice 的分数现在是 11 。
在第二轮中，Alice 将行分成 [6]，[2，3] 。
这一次 Bob 扔掉了左行，Alice 的分数变成了 16（11 + 5）。
最后一轮 Alice 只能将行分成 [2]，[3] 。
Bob 扔掉右行，Alice 的分数现在是 18（16 + 2）。游戏结束，因为这行只剩下一块石头了。

示例 2：
输入：stoneValue = [7,7,7,7,7,7,7]
输出：28

示例 3：
输入：stoneValue = [4]
输出：0

提示：
	1 <= stoneValue.length <= 500
	1 <= stoneValue[i] <= 10^6
*/

// https://leetcode.com/problems/stone-game-v/discuss/806761/Python-DP
// 抄的
class Solution
{
	vector<int> M;
	vector<array<int, 500>> buf;

	int dp(int i, int k)
	{
		if (i == k)
			return 0;
		int* ptr = &(buf[i][k]);
		if (*ptr)
			return *ptr;

		int ans = 0;
		for (int j = i; j < k; ++j)
		{
			int a = M[j + 1] - M[i];
			int b = M[k + 1] - M[j + 1];
			if (a <= b)
				ans = max(ans, a + dp(i, j));
			if (a >= b)
				ans = max(ans, b + dp(j + 1, k));
		}
		*ptr = ans;
		return ans;
	}

public:
	int stoneGameV(vector<int>& A)
	{
		int len = static_cast<int>(A.size());
		M.resize(len + 1);
		for (int i = 0; i < len; ++i)
			M[i + 1] = M[i] + A[i];
		buf.resize(len);
		memset(buf.data(), 0, len * sizeof(buf[0]));
		return dp(0, len - 1);
	}
};


int main()
{
	vector<int>
		a = { 6, 2, 3, 4, 5, 5 },
		b = { 7, 7, 7, 7, 7, 7, 7 },
		c = { 4 },
		d = { 2, 1, 1 },
		e = { 98, 77, 24, 49, 6, 12, 2, 44, 51, 96 };
	Solution s;
	OutExpr(s.stoneGameV(a), "%d");
	OutExpr(s.stoneGameV(b), "%d");
	OutExpr(s.stoneGameV(c), "%d");
	OutExpr(s.stoneGameV(d), "%d");
	OutExpr(s.stoneGameV(e), "%d");
}
