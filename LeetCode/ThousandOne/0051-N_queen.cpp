#include "leetcode.hpp"

/* 51. N皇后

n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

https://assets.leetcode.com/uploads/2018/10/12/8-queens.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/8-queens.png
上图为 8 皇后问题的一种解法。

给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例:

输入: 4
输出: [
 [".Q..",  // 解法 1
	"...Q",
	"Q...",
	"..Q."],

 ["..Q.",  // 解法 2
	"Q...",
	"...Q",
	".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。

提示：
	皇后，是国际象棋中的棋子，意味着国王的妻子。
	皇后只做一件事，那就是“吃子”。
	当她遇见可以吃的棋子时，就迅速冲上去吃掉棋子。
	当然，她横、竖、斜都可走一或七步，可进可退。
	（引用自 百度百科 - 皇后 ）
*/

class Solution
{
	struct Mask
	{
		unsigned cols, diag, anti;
	};

	int n;
	vector<vector<string>> ans;
	vector<unsigned> grid;
	Mask mask;

	void record()
	{
		vector<string> board(n);
		for (int h = 0; h < n; ++h)
		{
			board[h].resize(n, '.');
			for (int w = 0; w < n; ++w)
				if (grid[h] & (1U << w))
					board[h][w] = 'Q';
		}
		ans.push_back(std::move(board));
	}

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
				// 最后一行不可能有两种填法
				record();
				break;
			}
			mask = oldm;
			grid[h] = oldg;
		}
	}

public:
	vector<vector<string>> solveNQueens(int len)
	{
		n = len;
		assert(1 <= n && n <= 16);
		grid.assign(n, 0U);
		mask.cols = mask.diag = mask.anti = 0;
		dfs(0);
		vector<vector<string>> R;
		R.swap(ans);
		return R;
	}
};

int main()
{
	Solution s;
	vector<vector<string>> queen = s.solveNQueens(5);
	int len = static_cast<int>(queen.size());
	for (int i = 0; i < len; ++i)
	{
		printf("===== %2d =====\n", i);
		output(queen[i]);
	}
}
