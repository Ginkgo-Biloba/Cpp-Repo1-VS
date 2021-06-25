#include "leetcode.hpp"

/* 1770. 执行乘法运算的最大分数

给你两个长度分别 n 和 m 的整数数组 nums 和 multipliers ，其中 n >= m ，数组下标 从 1 开始 计数。

初始时，你的分数为 0 。
你需要执行恰好 m 步操作。
在第 i 步操作（从 1 开始 计数）中，需要：
	选择数组 nums 开头处或者末尾处 的整数 x 。
	你获得 multipliers[i] * x 分，并累加到你的分数中。
	将 x 从数组 nums 中移除。
在执行 m 步操作后，返回 最大 分数。

示例 1：
输入：nums = [1,2,3], multipliers = [3,2,1]
输出：14
解释：一种最优解决方案如下：
- 选择末尾处的整数 3 ，[1,2,3] ，得 3 * 3 = 9 分，累加到分数中。
- 选择末尾处的整数 2 ，[1,2] ，得 2 * 2 = 4 分，累加到分数中。
- 选择末尾处的整数 1 ，[1] ，得 1 * 1 = 1 分，累加到分数中。
总分数为 9 + 4 + 1 = 14 。

示例 2：
输入：nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
输出：102
解释：一种最优解决方案如下：
- 选择开头处的整数 -5 ，[-5,-3,-3,-2,7,1] ，得 -5 * -10 = 50 分，累加到分数中。
- 选择开头处的整数 -3 ，[-3,-3,-2,7,1] ，得 -3 * -5 = 15 分，累加到分数中。
- 选择开头处的整数 -3 ，[-3,-2,7,1] ，得 -3 * 3 = -9 分，累加到分数中。
- 选择末尾处的整数 1 ，[-2,7,1] ，得 1 * 4 = 4 分，累加到分数中。
- 选择末尾处的整数 7 ，[-2,7] ，得 7 * 6 = 42 分，累加到分数中。
总分数为 50 + 15 - 9 + 4 + 42 = 102 。

提示：
	n == nums.length
	m == multipliers.length
	1 <= m <= 10^3
	m <= n <= 10^5
	-1000 <= nums[i], multipliers[i] <= 1000
*/

// https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/
// 抄的
class Solution
{
	int n, m;
	vector<int> A, B;
	vector<array<int, 1002>> buf;

	int dp(int i, int j)
	{
		if (j == m)
			return 0;
		if (buf[i][j] != -1)
			return buf[i][j];
		int left = dp(i + 1, j + 1) + A[i] * B[j];
		int right = dp(i, j + 1) + A[n - (j - i) - 1] * B[j];
		return buf[i][j] = max(left, right);
	}

public:
	int maximumScore(vector<int>& nums, vector<int>& multipliers)
	{
		A = nums;
		B = multipliers;
		n = static_cast<int>(A.size());
		m = static_cast<int>(B.size());
		buf.resize(m + 2);
		memset(buf.data(), -1, buf.size() * sizeof(buf[0]));
		return dp(0, 0);
	}
};


int main()
{
	vector<int>
		a = { 1, 2, 3 },
		b = { 3, 2, 1 },
		c = { -5, -3, -3, -2, 7, 1 },
		d = { -10, -5, 3, 4, 6 };
	Solution s;
	OutExpr(s.maximumScore(a, b), "%d");
	OutExpr(s.maximumScore(c, d), "%d");
}
