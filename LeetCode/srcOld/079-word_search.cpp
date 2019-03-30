#include "../srcOld/utility.hpp"


bool exist_dfs(vector<vector<char>> const& board, string const& word, \
	string& cur, int rows, int cols, int R, int C, vector<char>& flag)
{
	if (board[R][C] != word[cur.size()]) return false;
	char& f = flag[R * cols + C];
	if (f)
		return false;

	cur.push_back(board[R][C]); f = 1;
	if (cur == word)
		return true;
	if (cur.size() >= word.size())
	{
		cur.pop_back(); f = 0;
		return false;
	}
	bool ans = false;

	if (/*!ans &&*/ R + 1 < rows)
		ans = exist_dfs(board, word, cur, rows, cols, R + 1, C, flag);
	if (!ans && (R - 1 >= 0))
		ans = exist_dfs(board, word, cur, rows, cols, R - 1, C, flag);
	if (!ans && (C + 1 < cols))
		ans = exist_dfs(board, word, cur, rows, cols, R, C + 1, flag);
	if (!ans && (C - 1 >= 0))
		ans = exist_dfs(board, word, cur, rows, cols, R, C - 1, flag);

	if (!ans)
	{ cur.pop_back(); f = 0; }
	return ans;
}

bool exist(vector<vector<char>> const& board, string const& word)
{
	int const rows = static_cast<int>(board.size());
	int const cols = static_cast<int>(board[0].size());
	if (word.empty()) return false;
	if ((rows * cols < word.size())) return false;
	char const ch = word[0];
	string cur;
	bool ans = false;
	vector<char> flag(static_cast<size_t>(rows * cols), static_cast<char>(0));

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
		{
			if (board[r][c] == ch)
			{
				ans = exist_dfs(board, word, cur, rows, cols, r, c, flag);
				if (ans) return true;
				// memset(flag.data(), 0x00, rows * cols * sizeof(char));
			}
		}

	return false;
}



int main()
{
	vector<vector<char>> grid = \
		{ { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } };
	int ans = exist(grid, string("ABCCED"));
	printf("%1s = %d\n", "exist", ans);
}
