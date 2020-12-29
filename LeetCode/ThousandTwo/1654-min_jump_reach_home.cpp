#include "leetcode.hpp"

/* 1654. 到家的最少跳跃次数

有一只跳蚤的家在数轴上的位置 x 处。
请你帮助它从位置 0 出发，到达它的家。
跳蚤跳跃的规则如下：
	它可以 往前 跳恰好 a 个位置（即往右跳）。
	它可以 往后 跳恰好 b 个位置（即往左跳）。
	它不能 连续 往后跳 2 次。
	它不能跳到任何 forbidden 数组中的位置。

跳蚤可以往前跳 超过 它的家的位置，但是它 不能跳到负整数 的位置。

给你一个整数数组 forbidden ，其中 forbidden[i] 是跳蚤不能跳到的位置，同时给你整数 a， b 和 x ，请你返回跳蚤到家的最少跳跃次数。
如果没有恰好到达 x 的可行方案，请你返回 -1 。

示例 1：
输入：forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
输出：3
解释：往前跳 3 次（0 -> 3 -> 6 -> 9），跳蚤就到家了。

示例 2：
输入：forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
输出：-1

示例 3：
输入：forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
输出：2
解释：往前跳一次（0 -> 16），然后往回跳一次（16 -> 7），跳蚤就到家了。

提示：
	1 <= forbidden.length <= 1000
	1 <= a, b, forbidden[i] <= 2000
	0 <= x <= 2000
	forbidden 中所有位置互不相同。
	位置 x 不在 forbidden 中。
*/

// https://leetcode.com/problems/minimum-jumps-to-reach-home/discuss/935419/Python-deque-BFS-O(max(x-max(forbidden))%2Ba%2Bb)
// 抄的
int minimumJumps(vector<int>& forbidden, int a, int b, int x)
{
	vector<int> S;
	int right = x;
	for (int i : forbidden)
		right = max(right, i);
	right += a + b;
	S.resize(right + 1, INT_MAX);
	for (int i : forbidden)
		S[i] = -1;
	S[0] = 0;
	deque<int> Q;
	Q.push_back(0);
	while (!Q.empty())
	{
		int i = Q.front();
		int s = S[i];
		Q.pop_front();
		int k = i + a;
		int t = s + 1;
		if (k <= right && t < S[k])
		{
			S[k] = t;
			Q.push_back(k);
		}
		k = i - b;
		if (k > 0 && t < S[k])
		{
			S[k] = t;
			k = k + a;
			t = s + 2;
			if (k <= right && t < S[k])
			{
				S[k] = t;
				Q.push_back(k);
			}
		}
		if (S[x] <= right)
			return S[x];
	}
	return -1;
}


int main()
{
	vector<int>
		a = { 14, 4, 18, 1, 15 },
		b = { 8, 3, 16, 6, 12, 20 },
		c = { 1, 6, 2, 14, 5, 17, 4 };
	OutExpr(minimumJumps(a, 3, 15, 9), "%d");
	OutExpr(minimumJumps(b, 15, 13, 11), "%d");
	OutExpr(minimumJumps(c, 16, 9, 7), "%d");
}
