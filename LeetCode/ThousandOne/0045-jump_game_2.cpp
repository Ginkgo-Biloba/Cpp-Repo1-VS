#include "leetcode.hpp"

/* 45. 跳跃游戏 II

给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

示例:
输入: [2,3,1,1,4]
输出: 2
解释:
跳到最后一个位置的最小跳跃数是 2。
从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。

说明:
假设你总是可以到达数组的最后一个位置。
*/

// https://leetcode.com/problems/jump-game-ii/discuss/18089/Evolve-from-brute-force-to-optimal
// 抄的
int jump(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int pre = 0, cur = 0, step = 0;
	for (int i = 0; i < len; ++i)
	{
		if (i > pre)
		{
			step += 1;
			// 否则跳不到结尾
			assert(i <= cur);
			pre = cur;
		}
		cur = max(cur, i + A[i]);
	}
	return step;
}

int main()
{
	vector<int> a = { 2, 3, 1, 1, 4 };
	OutExpr(jump(a), "%d");
}
