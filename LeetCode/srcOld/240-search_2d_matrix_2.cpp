#include "../srcOld/utility.hpp"

bool searchMatrix(vector<vector<int>> &mat, int target)
{
	int const rows = static_cast<int>(mat.size());
	if (rows == 0)
		return false;
	int const cols = static_cast<int>(mat[0].size());

	int r = 0, c = cols - 1;
	while (r < rows && c >= 0)
	{
		int val = mat[r][c];
		if (val == target)
			return true;
		else if (val > target)
			--c;
		else
			++r;
	}

	return false;
}

