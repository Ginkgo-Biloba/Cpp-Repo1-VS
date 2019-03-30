#include "utility.hpp"

// 抄的
int maximalSquare(vector<vector<char>> const& matrix)
{
	if (matrix.empty()) return 0;
	size_t rows = matrix.size(), cols = matrix[0].size();
	if (cols == 0) return 0;

	vector<int> prev(cols), cur(cols, 0);
	int szMax = 0;

	for (size_t r = 0; r < rows; ++r)
	{
		char const* ptr = matrix[r].data();
		prev.swap(cur);
		cur[0] = ptr[0] - '0';
		szMax = std::max(szMax, cur[0]);
		for (size_t c = 1; c < cols; ++c)
		{
			if (ptr[c] == '1')
			{
				cur[c] = std::min(cur[c - 1], std::min(prev[c - 1], prev[c]));
				cur[c] += 1;
				szMax = std::max(szMax, cur[c]);
			}
			else cur[c] = 0;
		}
	}
	return static_cast<int>(szMax) * szMax;
}


int main()
{
	vector<vector<char>> matrix =
	{
		{ '1', '0', '1', '0', '0' },
		{ '1', '0', '1', '1', '1' },
		{ '1', '1', '1', '1', '1' },
		{ '1', '0', '0', '1', '0' },
	};
	int ans = maximalSquare(matrix);
	printf("%1s = %d\n", "Maximal Square", ans);
}
