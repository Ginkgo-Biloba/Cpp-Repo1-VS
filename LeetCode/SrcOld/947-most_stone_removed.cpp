#include "leetcode.hpp"

/* 947. 移除最多的同行或同列石头

在二维平面上，我们将石头放置在一些整数坐标点上。
每个坐标点上最多只能有一块石头。

现在，move 操作将会移除与网格上的某一块石头共享一列或一行的一块石头。

我们最多能执行多少次 move 操作？

示例 1：
输入：stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
输出：5

示例 2：
输入：stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
输出：3

示例 3：
输入：stones = [[0,0]]
输出：0

提示：
	1 <= stones.length <= 1000
	0 <= stones[i][j] < 10000
*/


// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/discuss/197668/Count-the-Number-of-Islands-O(N)
// 抄的
class Solution
{
	unordered_map<int, int> par;
	int island;

	int findpar(int x)
	{
		if (par.find(x) == par.end())
		{
			par[x] = x;
			++island;
		}
		if (par[x] != x)
			par[x] = findpar(par[x]);
		return par[x];
	}

	void uni(int x, int y)
	{
		int px = findpar(x);
		int py = findpar(y);
		if (px != py)
		{
			par[x] = par[y] = par[px] = py;
			--island;
		}
	}

public:
	int removeStones(vector<vector<int>>& A)
	{
		island = 0;
		par.clear();
		for (auto const& a : A)
			uni(a[0], ~a[1]);
		return static_cast<int>(A.size()) - island;
	}
};

int main()
{
	vector<vector<int>>
		a = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 2 }, { 2, 1 }, { 2, 2 } },
		b = { { 0, 0 }, { 0, 2 }, { 1, 1 }, { 2, 0 }, { 2, 2 } },
		c = { { 0, 0 } };
	Solution s;
	OutExpr(s.removeStones(a), "%d");
	OutExpr(s.removeStones(b), "%d");
	OutExpr(s.removeStones(c), "%d");
}
