#include "../src/utility.hpp"


bool searchMatrix(vector<vector<int>>& matrix, int target)
{
	if (matrix.empty()) return false;
	int const rows = static_cast<int>(matrix.size());
	int const cols = static_cast<int>(matrix[0].size());

	int cur, r = 0, c = cols - 1;
	while ((r < rows) && (c >= 0))
	{
		cur = matrix[r][c];
		if (cur == target)
			return true;
		else if (cur > target)
			--c;
		else
			++r;
	}
	return false;
}


int main()
{
	vector<vector<int>>	grid = {
		{ 1, 3, 5, 7 },
		{ 10, 11, 16, 20 },
		{ 23, 30, 34, 50 }
	};
	int ans = searchMatrix(grid, 11);
	printf("%1s = %d\n", "searchMatrix", ans);
}
