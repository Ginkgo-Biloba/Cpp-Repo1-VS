#include "leetcode.hpp"

/* 1444. 切披萨的方案数

给你一个 rows x cols 大小的矩形披萨和一个整数 k ，矩形包含两种字符： 'A' （表示苹果）和 '.' （表示空白格子）。你需要切披萨 k-1 次，得到 k 块披萨并送给别人。

切披萨的每一刀，先要选择是向垂直还是水平方向切，再在矩形的边界上选一个切的位置，将披萨一分为二。如果垂直地切披萨，那么需要把左边的部分送给一个人，如果水平地切，那么需要把上面的部分送给一个人。在切完最后一刀后，需要把剩下来的一块送给最后一个人。

请你返回确保每一块披萨包含 至少 一个苹果的切披萨方案数。
由于答案可能是个很大的数字，请你返回它对 10^9 + 7 取余的结果。

示例 1：
https://assets.leetcode.com/uploads/2020/04/23/ways_to_cut_apple_1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/10/ways_to_cut_apple_1.png
输入：pizza = ["A..","AAA","..."], k = 3
输出：3
解释：上图展示了三种切披萨的方案。注意每一块披萨都至少包含一个苹果。

示例 2：
输入：pizza = ["A..","AA.","..."], k = 3
输出：1

示例 3：
输入：pizza = ["A..","A..","..."], k = 1
输出：1

提示：
	1 <= rows, cols <= 50
	rows == pizza.length
	cols == pizza[i].length
	1 <= k <= 10
	pizza 只包含字符 'A' 和 '.' 。
*/


class Solution
{
	enum { mod = static_cast<int>(1e9 + 7) };

	int buffer[50][50][10];
	int acmlt[51][51];
	int rows, cols;

	int dp(int h, int w, int k)
	{
		int sum = acmlt[h][w];
		if (k == 1)
			return sum > 0;
		if (sum == 0)
			return 0;

		int val = buffer[h][w][k - 1];
		if (val >= 0)
			return val;

		val = 0;
		for (int y = h + 1; y <= rows; ++y)
		{
			int rest = acmlt[y][w];
			if (sum > rest && rest >= 0)
				val = (val + dp(y, w, k - 1)) % mod;
		}
		for (int x = w + 1; x <= cols; ++x)
		{
			int rest = acmlt[h][x];
			if (sum > rest && rest >= 0)
				val = (val + dp(h, x, k - 1)) % mod;
		}

		buffer[h][w][k - 1] = val;
		return val;
	}

public:
	int ways(vector<string>& pizza, int k)
	{
		rows = static_cast<int>(pizza.size());
		cols = static_cast<int>(pizza[0].size());
		memset(acmlt, 0, sizeof(acmlt));
		for (int h = rows - 1; h >= 0; --h)
		{
			int cur = 0;
			for (int w = cols - 1; w >= 0; --w)
			{
				cur += pizza[h][w] == 'A';
				acmlt[h][w] = acmlt[h + 1][w] + cur;
			}
		}

		memset(buffer, 0xff, sizeof(buffer));
		return dp(0, 0, k);
	}
};


int main()
{
	vector<string>
		a = { "A..", "AAA", "..." },
		b = { "A..", "AA.", "..." },
		c = { "A..", "A..", "..." };
	Solution s;
	OutExpr(s.ways(a, 3), "%d");
	OutExpr(s.ways(b, 3), "%d");
	OutExpr(s.ways(c, 1), "%d");
}
