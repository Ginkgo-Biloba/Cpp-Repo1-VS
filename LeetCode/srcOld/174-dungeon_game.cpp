#include "leetcode.hpp"

/* 174. Dungeon Game */

int calculateMinimumHP(vector<vector<int>>& grid)
{
	int const height = grid.size();
	if (height == 0)return 0;
	int const width = grid[0].size();
	if (width == 0) return 1;
	int h = height - 1, w = width - 1;
	int const* S; int* D = grid[height - 1].data();

	D[w] = 1 + std::max(0, -D[w]);
	for (; w > 0; --w)
		D[w - 1] = std::max(1, D[w] - D[w - 1]);
	for (; h > 0; --h)
	{
		S = grid[h].data();
		D = grid[h - 1].data();
		w = width - 1;
		D[w] = std::max(1, S[w] - D[w]);
		for (; w > 0; --w)
			D[w - 1] = std::max(1, std::min(D[w], S[w - 1]) - D[w - 1]);
	}

	return grid[0][0];
}




int main()
{
	vector<vector<int>> grid = {
		{ -2, -3, 3 },
		{ -5, -10, 1 },
		{ 10, 30, -5 } };
	int ans = calculateMinimumHP(grid);
	printf("%s: %d\n", "calculateMinimumHP", ans);
}
