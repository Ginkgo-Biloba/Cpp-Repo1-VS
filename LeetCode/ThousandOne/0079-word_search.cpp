#include "leetcode.hpp"

/* 79. 单词搜索

给定一个二维网格和一个单词，找出该单词是否存在于网格中。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。

示例:

board =
[
	['A','B','C','E'],
	['S','F','C','S'],
	['A','D','E','E']
]

给定 word = "ABCCED", 返回 true
给定 word = "SEE", 返回 true
给定 word = "ABCB", 返回 false

提示：
	board 和 word 中只包含大写和小写英文字母。
	1 <= board.length <= 200
	1 <= board[i].length <= 200
	1 <= word.length <= 10^3
*/

class Solution
{
	vector<vector<char>> board;
	string word;
	vector<char> visit;
	vector<pair<int, int>> current, nextloop;
	vector<int> cntB, cntW;
	unsigned rows, cols, wlen;

	unsigned at(unsigned h, unsigned w)
	{
		return h * cols + w;
	}

	bool dfs(unsigned h, unsigned w, unsigned i)
	{
		int const dir[] = { -1, 0, 1, 0, -1 };
		unsigned f = at(h, w);
		bool b = false;
		i += 1;
		if (i == wlen)
			return true;
		visit[f] = 1;
		for (int d = 0; (d < 4) && !b; ++d)
		{
			unsigned y = h + dir[d];
			unsigned x = w + dir[d + 1];
			if (y < rows && x < cols
				&& !(visit[at(y, x)])
				&& board[y][x] == word[i])
				b = dfs(y, x, i);
		}
		visit[f] = 0;
		return b;
	}


public:
	bool exist(vector<vector<char>>& board_, string word_)
	{
		board = board_;
		// board.swap(board_);
		word.swap(word_);
		rows = static_cast<unsigned>(board.size());
		cols = static_cast<unsigned>(board[0].size());
		wlen = static_cast<unsigned>(word.length());
		cntB.assign(128, 0);
		cntW.assign(128, 0);
		for (unsigned i = 0; i < wlen; ++i)
			cntW[word[i]] += 1;
		for (unsigned h = 0; h < rows; ++h)
			for (unsigned w = 0; w < cols; ++w)
				cntB[board[h][w]] += 1;
		for (unsigned i = 'A'; i <= 'z'; ++i)
		{
			if (cntB[i] < cntW[i])
				return false;
		}
		visit.assign(rows * cols, 0);
		for (unsigned h = 0; h < rows; ++h)
			for (unsigned w = 0; w < cols; ++w)
				if (board[h][w] == word[0])
				{
					bool b = dfs(h, w, 0);
					if (b)
						return true;
				}
		return false;
	}
};


int main()
{
	vector<vector<char>> a = {
		{ 'A', 'B', 'C', 'E' },
		{ 'S', 'F', 'C', 'S' },
		{ 'A', 'D', 'E', 'E' },
	};
	Solution s;
	OutBool(s.exist(a, "ABCCED"));
	OutBool(s.exist(a, "SEE"));
	OutBool(s.exist(a, "ABCB"));
}
