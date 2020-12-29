#include "leetcode.hpp"

/* 1696. 跳跃游戏 VI

给你一个下标从 0 开始的整数数组 nums 和一个整数 k 。

一开始你在下标 0 处。每一步，你最多可以往前跳 k 步，但你不能跳出数组的边界。
也就是说，你可以从下标 i 跳到 [i + 1， min(n - 1, i + k)] 包含 两个端点的任意位置。

你的目标是到达数组最后一个位置（下标为 n - 1 ），你的 得分 为经过的所有数字之和。

请你返回你能得到的 最大得分 。

示例 1：
输入：nums = [1,-1,-2,4,-7,3], k = 2
输出：7
解释：你可以选择子序列 [1,-1,4,3] （上面加粗的数字），和为 7 。

示例 2：
输入：nums = [10,-5,-2,4,0,3], k = 3
输出：17
解释：你可以选择子序列 [10,4,3] （上面加粗数字），和为 17 。

示例 3：
输入：nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
输出：0

提示：
1 <= nums.length, k <= 10^5
-104 <= nums[i] <= 10^4
*/

int maxResult(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	deque<pair<int, int>> Q;
	// 一开始不能给 {-1, 0}，万一前面 k 个都是负数就出事了
	Q.push_back({ 0, A[0] });
	for (int i = 1; i < len; ++i)
	{
		if (Q.front().first < i - k)
			Q.pop_front();
		int cur = Q.front().second + A[i];
		while (Q.size() && Q.back().second <= cur)
			Q.pop_back();
		Q.push_back({ i, cur });
	}
	return Q.back().second;
}


int main()
{
	vector<int>
		a = { 1, -1, -2, 4, -7, 3 },
		b = { 10, -5, -2, 4, 0, 3 },
		c = { 1, -5, -20, 4, -1, 3, -6, -3 };
	OutExpr(maxResult(a, 2), "%d");
	OutExpr(maxResult(b, 3), "%d");
	OutExpr(maxResult(c, 2), "%d");
}
