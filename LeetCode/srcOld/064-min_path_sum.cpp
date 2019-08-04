#include "leetcode.hpp"


int minPathSum(vector<vector<int>>& grid)
{
	unsigned const rows = static_cast<unsigned>(grid.size());
	unsigned const cols = static_cast<unsigned>(grid[0].size());
	if (!rows || !cols) return 0;

	int* prev = grid[0].data();
	for (unsigned c = 1u; c < cols; c++)
		prev[c] += prev[c - 1u];

	for (unsigned r = 1u; r < rows; r++)
	{
		int* cur = grid[r].data();
		cur[0] += prev[0];
		for (unsigned c = 1u; c < cols; c++)
			cur[c] += std::min(cur[c - 1u], prev[c]);
		prev = cur;
	}

	return prev[cols - 1u];
}


int main()
{
	vector<vector<int>> grid = { { 1, 3, 1 }, { 1, 5, 1 }, { 4, 2, 1 } };
	int ans = minPathSum(grid);
	printf("%1s = %d\n", "minPathSum", ans);
}
