#include "../src/utility.hpp"

void setZeroes(vector<vector<int>>& matrix)
{
	int const rows = static_cast<int>(matrix.size());
	int const cols = static_cast<int>(matrix[0].size());
	size_t const szCol = sizeof(int) * matrix[0].size();
	int col0 = 1;
	int* start = matrix[0].data();

	for (int r = 0; r < rows; ++r)
	{
		int* ptr = matrix[r].data();
		if (ptr[0] == 0) col0 = 0;
		for (int c = 1; c < cols; ++c)
		{
			if (ptr[c] == 0)
				ptr[0] = start[c] = 0;
		}
	}

	for (int r = 1; r < rows; ++r)
	{
		int* ptr = matrix[r].data();
		if (ptr[0] == 0)
			memset(ptr, 0x00, szCol);
		else
		{
			if (col0 == 0) ptr[0] = 0;
			for (int c = 1; c < cols; ++c)
			{
				if (start[c] == 0)
					ptr[c] = 0;
			}
		}
	}
	if (start[0] == 0)
		memset(start, 0x00, szCol);
	else if (col0 == 0)
		start[0] = 0;
}


int main()
{
	vector<vector<int>>	grid = { { 1, 1, 1 }, { 0, 1, 2 } };
	setZeroes(grid);
	output(grid, "setZeroes");
}
