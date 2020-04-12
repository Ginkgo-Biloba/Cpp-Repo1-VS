#include "leetcode.hpp"

/* 1240. 铺瓷砖

你是一位施工队的工长，根据设计师的要求准备为一套设计风格独特的房子进行室内装修。

房子的客厅大小为 n x m，为保持极简的风格，需要使用尽可能少的 正方形 瓷砖来铺盖地面。

假设正方形瓷砖的规格不限，边长都是整数。

请你帮设计师计算一下，最少需要用到多少块方形瓷砖？

示例 1：
https://assets.leetcode.com/uploads/2019/10/17/sample_11_1592.png
输入：n = 2, m = 3
输出：3
解释：3 块地砖就可以铺满卧室。
	2 块 1x1 地砖
	1 块 2x2 地砖

示例 2：
https://assets.leetcode.com/uploads/2019/10/17/sample_22_1592.png
输入：n = 5, m = 8
输出：5

示例 3：
https://assets.leetcode.com/uploads/2019/10/17/sample_33_1592.png
输入：n = 11, m = 13
输出：6

提示：
	1 <= n <= 13
	1 <= m <= 13
*/

// https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/discuss/414804/A-Review%3A-Why-This-Problem-Is-a-Tip-of-the-Iceberg
// 抄的
class Solution
{
	vector<int> height, buf;
	int n, m, ans;

	int& dp(int i, int k)
	{
		return buf[i * (m + 1) + k];
	}

	// (a) add DP upper bound
	// (b) use backtracking and pass array by reference to be memory efficient
	// (c) other minor changes such as removing redundant variables & rewriting conditions
	// (d) does not include the skyline record since it does not reduce time complexity significantly in tests
	// Time Complexity: O(m^n)
	// Space Complexity: O(n)
	void dfs(int count)
	{
		if (count >= ans)
			return;

		int left = 0, minh = m;
		for (int i = 0; i < n; ++i)
			if (height[i] < minh)
			{
				minh = height[i];
				left = i;
			}

		if (minh == m)
		{
			ans = min(ans, count);
			return;
		}

		int right = left;
		while (right < n
			&& height[left] == height[right]
			&& right - left + minh < m)
			++right;

		for (int i = left; i < right; ++i)
			height[i] += right - left;

		// plot the biggest possible square to the rectangle
		for (int len = right - left; len >= 1; --len)
		{
			dfs(count + 1);
			// update the rectangle to contain the next smaller square
			for (int i = left; i < left + len - 1; ++i)
				height[i] -= 1;
			height[left + len - 1] -= len;
		}
	}

public:
	int tilingRectangle(int _n, int _m)
	{
		n = _n;
		m = _m;
		if (n == m)
			return 1;
		if (n > m)
			std::swap(n, m);
		height.resize(n);
		buf.resize((n + 1) * (m + 1));
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
			{
				if (i == j)
				{
					dp(i, j) = 1;
					continue;
				}
				dp(i, j) = i * j;
				for (int k = 1; k <= i / 2; ++k)
					dp(i, j) = min(dp(i, j), dp(i - k, j) + dp(k, j));
				for (int k = 1; k <= j / 2; ++k)
					dp(i, j) = min(dp(i, j), dp(i, j - k) + dp(i, k));
			}

		ans = dp(n, m);
		dfs(0);
		return ans;
	}
};


int main()
{
	Solution s;
	OutExpr(s.tilingRectangle(2, 3), "%d");
	OutExpr(s.tilingRectangle(5, 8), "%d");
	OutExpr(s.tilingRectangle(11, 13), "%d");
}
