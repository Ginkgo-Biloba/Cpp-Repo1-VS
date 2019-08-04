#include "leetcode.hpp"

int uniquePaths(int m, int n)
{
	if (m < 2 || n < 2) return 1;

	uint64_t r = m + n - 2;
	uint64_t p = std::min(m, n) - 1;
	uint64_t q = r - p + 1u;
	uint64_t l = 2u;
	uint64_t ans = 1u;

	for (; r >= q; --r)
	{
		if (ans / l * l == ans && l <= p)
		{ ans /= l; ++l; }
		ans *= r;
	}
	for (; l <= p; ++l)
		ans /= l;

	return static_cast<int>(ans);
}

int uniquePathsWithObstacles(int** grid, int rows, int cols)
{
	if (grid[0][0]) return 0;
	int* buf = (int*)(malloc(cols * sizeof(int)));
	memset(buf, 0x00, cols * sizeof(int));
	buf[0] = 1;

	for (int c = 1; c < cols; c++)
	{
		buf[c] = grid[0][c] ? 0 : buf[c - 1];
	}

	for (int r = 1; r < rows; r++)
	{
		if (grid[r][0]) buf[0] = 0;
		for (int c = 1; c < cols; c++)
		{
			buf[c] = grid[r][c] ? 0 : (buf[c] + buf[c - 1]);
		}
	}

	int ans = buf[cols - 1];
	free(buf);
	return ans;
}


int main()
{
	int ans = uniquePaths(10, 10);
	printf("%1s = %d\n", "uniquePaths", ans);
}
