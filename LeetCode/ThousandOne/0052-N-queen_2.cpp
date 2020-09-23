#include "leetcode.hpp"

/* 52. N皇后 II

n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

上图为 8 皇后问题的一种解法。

给定一个整数 n，返回 n 皇后不同的解决方案的数量。

示例:
输入: 4
输出: 2
解释: 4 皇后问题存在如下两个不同的解法。
[
 [".Q..",  // 解法 1
	"...Q",
	"Q...",
	"..Q."],

 ["..Q.",  // 解法 2
	"Q...",
	"...Q",
	".Q.."]
]

提示：
	皇后，是国际象棋中的棋子，意味着国王的妻子。
	皇后只做一件事，那就是“吃子”。
	当她遇见可以吃的棋子时，就迅速冲上去吃掉棋子。
	当然，她横、竖、斜都可走一或七步，可进可退。
	（引用自 百度百科 - 皇后 ）
*/

class Solution_Org
{
	struct Mask
	{
		unsigned cols, diag, anti;
	};

	int n, ans;
	vector<unsigned> grid;
	Mask mask;

	void dfs(int h)
	{
		Mask oldm = mask;
		unsigned oldg = grid[h];
		for (int w = 0; w < n; ++w)
		{
			unsigned mc = 1U << w;
			unsigned md = 1U << (15 + h - w);
			unsigned ma = 1U << (h + w);
			if ((mask.cols & mc)
				|| (mask.diag & md)
				|| (mask.anti & ma))
				continue;
			mask.cols |= mc;
			mask.diag |= md;
			mask.anti |= ma;
			grid[h] = mc;
			if (h + 1 < n)
				dfs(h + 1);
			else
			{
				++ans;
				break;
			}
			mask = oldm;
			grid[h] = oldg;
		}
	}

public:
	int totalNQueens(int len)
	{
		n = len;
		assert(1 <= n && n <= 16);
		grid.assign(n, 0U);
		ans = 0;
		mask.cols = mask.diag = mask.anti = 0;
		dfs(0);
		return ans;
	}
};


// http://www.matrix67.com/blog/archives/266
// 抄的
class Solution
{
	int n, ans, mask;

	void valid(int cols, int diag, int anti)
	{
		// 所有可以放的列
		int pos = mask & (~(cols | diag | anti));
		while (pos)
		{
			int p = pos & (-pos); // pos & (~(pos - 1))
			pos ^= p; // 清除这一列的放置标记
			if ((cols | p) == mask)
			{
				++ans;
				break;
			}
			valid(cols | p, (diag | p) >> 1, (anti | p) << 1);
		}
	}

public:
	int totalNQueens(int len)
	{
		n = len;
		assert(1 <= n && n <= 16);
		ans = 0;
		mask = (1 << n) - 1;
		valid(0, 0, 0);
		return ans;
	}
};


int main()
{
	Solution s;
	for (int i = 1; i <= 15; ++i)
		printf("%2d: %d\n", i, s.totalNQueens(i));
}
