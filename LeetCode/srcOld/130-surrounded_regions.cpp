#include "../src/utility.hpp"


class Solution
{
	vector<pair<int, int>> points;
	int rows, cols;

public:
	/** 区域生长算法，把与边界上的 O 相连的 O 改为 Y */
	void regionGrow(vector<vector<char>>& board, int r, int c)
	{
		points.emplace_back(r, c);
		while (!points.empty())
		{
			pair<int, int> pt = points.back(); points.pop_back();
			if (board[pt.first][pt.second] != 'O') continue;

			board[pt.first][pt.second] = 'Y';
			if (pt.first > 0)
				points.emplace_back(pt.first - 1, pt.second);
			if (pt.first < rows - 1)
				points.emplace_back(pt.first + 1, pt.second);
			if (pt.second > 0)
				points.emplace_back(pt.first, pt.second - 1);
			if (pt.second < cols - 1)
				points.emplace_back(pt.first, pt.second + 1);
		}
	}

	void solve(vector<vector<char>>& board)
	{
		if (board.empty()) return;
		if (board[0].empty()) return;
		rows = static_cast<int>(board.size());
		cols = static_cast<int>(board[0].size());

		for (int r = 0; r < rows; ++r)
		{
			char* ptr = board[r].data();
			if ((r == 0) || (r == rows - 1))
			{
				for (int c = 0; c < cols; ++c)
				{
					if (ptr[c] == 'O')
						regionGrow(board, r, c);
				}
			}
			else
			{
				if (ptr[0] == 'O')
					regionGrow(board, r, 0);
				if (ptr[cols - 1] == 'O')
					regionGrow(board, r, cols - 1);
			}
		}

		for (int r = 0; r < rows; ++r)
		{
			char* ptr = board[r].data();
			for (int c = 0; c < cols; ++c)
			{
				if (ptr[c] == 'O') ptr[c] = 'X';
				else if (ptr[c] == 'Y') ptr[c] = 'O';
			}
		}
	}
};


int main()
{
	
}
