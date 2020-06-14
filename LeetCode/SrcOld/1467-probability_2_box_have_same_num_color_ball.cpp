#include "leetcode.hpp"

/* 1467. 两个盒子中球的颜色数相同的概率

桌面上有 2n 个颜色不完全相同的球，球上的颜色共有 k 种。
给你一个大小为 k 的整数数组 balls ，其中 balls[i] 是颜色为 i 的球的数量。

所有的球都已经 随机打乱顺序 ，前 n 个球放入第一个盒子，后 n 个球放入另一个盒子（请认真阅读示例 2 的解释部分）。

注意：这两个盒子是不同的。
例如，两个球颜色分别为 a 和 b，盒子分别为 [] 和 ()，那么 [a] (b) 和 [b] (a) 这两种分配方式是不同的（请认真阅读示例 1 的解释部分）。

请计算「两个盒子中球的颜色数相同」的情况的概率。

示例 1：
输入：balls = [1,1]
输出：1.00000
解释：球平均分配的方式只有两种：
- 颜色为 1 的球放入第一个盒子，颜色为 2 的球放入第二个盒子
- 颜色为 2 的球放入第一个盒子，颜色为 1 的球放入第二个盒子
这两种分配，两个盒子中球的颜色数都相同。所以概率为 2/2 = 1 。

示例 2：
输入：balls = [2,1,1]
输出：0.66667
解释：球的列表为 [1, 1, 2, 3]
随机打乱，得到 12 种等概率的不同打乱方案，每种方案概率为 1/12 ：
[1,1 / 2,3], [1,1 / 3,2], [1,2 / 1,3], [1,2 / 3,1], [1,3 / 1,2], [1,3 / 2,1], [2,1 / 1,3], [2,1 / 3,1], [2,3 / 1,1], [3,1 / 1,2], [3,1 / 2,1], [3,2 / 1,1]
然后，我们将前两个球放入第一个盒子，后两个球放入第二个盒子。
这 12 种可能的随机打乱方式中的 8 种满足「两个盒子中球的颜色数相同」。
概率 = 8/12 = 0.66667

示例 3：
输入：balls = [1,2,1,2]
输出：0.60000
解释：球的列表为 [1, 2, 2, 3, 4, 4]。要想显示所有 180 种随机打乱方案是很难的，但只检查「两个盒子中球的颜色数相同」的 108 种情况是比较容易的。
概率 = 108 / 180 = 0.6 。

示例 4：
输入：balls = [3,2,1]
输出：0.30000
解释：球的列表为 [1, 1, 1, 2, 2, 3]。要想显示所有 60 种随机打乱方案是很难的，但只检查「两个盒子中球的颜色数相同」的 18 种情况是比较容易的。
概率 = 18 / 60 = 0.3 。

示例 5：
输入：balls = [6,6,6,6,6,6]
输出：0.90327

提示：
	1 <= balls.length <= 8
	1 <= balls[i] <= 6
	sum(balls) 是偶数
	答案与真实值误差在 10^-5 以内，则被视为正确答案
*/

// https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/discuss/661730/C%2B%2B-Backtrack-with-explanation
// 抄的
class Solution
{
	// 组合 C{n, k}
	int C[9][9], len, half;
	double valid, total;
	vector<int> ball;

	void dfs(int a, int b, int ka, int kb, int i, double s)
	{
		if ((a > half) || (b > half))
			return;
		if (i == len)
		{
			// 因为总和为偶数，且都不大于 half
			assert(a == b);
			valid += (ka == kb) * s;
			total += s;
			return;
		}
		int n = ball[i];
		int m = i + 1;
		for (int k = 0; k <= n; ++k)
		{
			int c = a + k;
			int d = b + n - k;
			int kc = ka + (k > 0);
			int kd = kb + (k < n);
			dfs(c, d, kc, kd, m, s * C[n][k]);
		}
	}

public:
	double getProbability(vector<int>& _balls)
	{
		memset(C, 0, sizeof(C));
		for (int n = 0; n <= 8; ++n)
		{
			C[n][n] = C[n][0] = 1;
			for (int k = 1; k < n; ++k)
				C[n][k] = C[n - 1][k] + C[n - 1][k - 1];
		}

		ball.swap(_balls);
		len = static_cast<int>(ball.size());
		valid = total = half = 0;
		for (int i = 0; i < len; ++i)
			half += ball[i];
		half /= 2;
		dfs(0, 0, 0, 0, 0, 1.0);

		return (total > 0.0) ? (valid / total) : 0.0;
	}
};


int main()
{
	vector<int>
		a = { 1, 1 },
		b = { 2, 1, 1 },
		c = { 1, 2, 1, 2 },
		d = { 3, 2, 1 },
		e = { 6, 6, 6, 6, 6, 6 };
	Solution s;
	OutExpr(s.getProbability(a), "%f");
	OutExpr(s.getProbability(b), "%f");
	OutExpr(s.getProbability(c), "%f");
	OutExpr(s.getProbability(d), "%f");
	OutExpr(s.getProbability(e), "%f");
}
