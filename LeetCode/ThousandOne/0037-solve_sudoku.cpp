#include "leetcode.hpp"

/* 37. 解数独

编写一个程序，通过已填充的空格来解决数独问题。

一个数独的解法需遵循如下规则：
	数字 1-9 在每一行只能出现一次。
	数字 1-9 在每一列只能出现一次。
	数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

空白格用 '.' 表示。

http://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png
一个数独。

http://upload.wikimedia.org/wikipedia/commons/thumb/3/31/Sudoku-by-L2G-20050714_solution.svg/250px-Sudoku-by-L2G-20050714_solution.svg.png
答案被标成红色。

Note:
	给定的数独序列只包含数字 1-9 和字符 '.' 。
	你可以假设给定的数独只有唯一解。
	给定数独永远是 9x9 形式的。
*/

// https://leetcode.com/problems/sudoku-solver/discuss/15748/Sharing-my-2ms-C%2B%2B-solution-with-comments-and-explanations.
// 抄的
class Solution
{
	typedef unsigned char uchar;
	typedef unsigned short ushort;

	struct cell
	{
		uchar val; // 填的值
		uchar numtry; // 可以填的值的个数
		ushort forbid; // 不能填的值，如果该位是 1
	};

	struct point
	{
		int y, x;
	};


	cell grid[9][9];
	// backtracking state - list of empty cells
	vector<point> bt;

	ushort bitmask(int v)
	{
		return static_cast<ushort>(1 << v);
	}

	// sets the value of the cell to [v]
	// the function also propagates constraints to other cells and deduce new values where possible
	bool set(int h, int w, int v);

	// update constraints of the cell i,j by excluding possibility of 'excludedValue'
	// once there's one possibility left the function recurses back into set()
	bool update(int h, int w, int exv)
	{
		ushort mask = bitmask(exv);
		cell& c = grid[h][w];
		if (c.forbid & mask)
			return true;
		if (c.val == exv)
			return false;
		c.forbid |= mask;
		--(c.numtry);
		if (c.numtry > 1)
			return true;
		for (int v = 1; v <= 9; ++v)
		{
			if (!(c.forbid & mask))
				return set(h, w, v);
		}
		assert(false);
		return false;
	}

	// finds value for all empty cells with index >=k
	bool backtrack(int k);

	// find values for empty cells
	bool findval()
	{
		bt.clear();
		bt.reserve(81);
		for (int h = 0; h < 9; ++h)
			for (int w = 0; w < 9; ++w)
			{
				if (!(grid[h][w].val))
					bt.push_back({ h, w });
			}
		sort(bt.begin(), bt.end(),
			[this](point const& a, point& b) -> bool
		{
			return grid[a.y][a.x].numtry < grid[b.y][b.x].numtry;
		});
		return backtrack(0);
	}

public:
	void solveSudoku(vector<vector<char>>& board)
	{
		// clear array
		memset(grid, 0, sizeof(grid));
		// Decoding input board into the internal cell matrix.
		// As we do it - constraints are propagated and even additional values are set as we go in the case if it is possible to unambiguously deduce them
		for (int h = 0; h < 9; ++h)
			for (int w = 0; w < 9; ++w)
			{
				if (board[h][w] == '.')
					continue;
				int v = board[h][w] - '0';
				// sudoku is either incorrect or unsolvable
				if (!set(h, w, v))
					return;
			}

		// if we're lucky we've already got a solution,
		// however, if we have empty cells we need to use backtracking to fill them.
		// try to solve, and if sudoku is unsolvable, return
		if (!findval())
			return;

		// copying the solution back to the board
		for (int h = 0; h < 9; ++h)
			for (int w = 0; w < 9; ++w)
			{
				if (grid[h][w].val)
					board[h][w] = static_cast<char>(grid[h][w].val + '0');
			}
	}
};


bool Solution::set(int h, int w, int v)
{
	ushort mask = bitmask(v);
	cell& c = grid[h][w];
	if (c.val == v)
		return true;
	if (c.forbid & mask)
		return false;
	c.forbid = 0xffff;
	c.forbid ^= mask;
	c.numtry = 1;
	c.val = static_cast<uchar>(v);

	int T = h / 3 * 3;
	int L = w / 3 * 3;
	// propagating constraints
	for (int k = 0; k < 9; ++k)
	{
		// to the row
		if ((h != k) && !update(k, w, v))
			return false;
		// to the column
		if ((w != k) && !update(h, k, v))
			return false;
		// to the 3x3 square
		int y = T + k / 3;
		int x = L + k % 3;
		if ((y != h) && (x != w) && !update(y, x, v))
			return false;
	}
	return true;
}


bool Solution::backtrack(int k)
{
	int len = static_cast<int>(bt.size());
	if (k >= len)
		return true;
	int h = bt[k].y;
	int w = bt[k].x;
	// fast path - only 1 possibility
	if (grid[h][w].val)
		return backtrack(k + 1);
	ushort forbid = grid[h][w].forbid;
	// slow path >1 possibility.
	// making snapshot of the state
	cell backup[9][9];
	memcpy(backup, grid, sizeof(grid));
	for (int v = 1; v <= 9; ++v)
		if (!(forbid & bitmask(v)))
		{
			if (set(h, w, v) && backtrack(k + 1))
				return true;
			// restoring from snapshot,
			// note: computationally this is cheaper
			// than alternative implementation with undoing the changes
			memcpy(grid, backup, sizeof(grid));
		}
	return false;
}


int main()
{
	Solution s;
	vector<vector<char>> b = {
		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' },
	};
	s.solveSudoku(b);
	for (int h = 0; h < 9; ++h)
	{
		for (int w = 0; w < 9; ++w)
			putchar(b[h][w]);
		putchar('\n');
	}
}
