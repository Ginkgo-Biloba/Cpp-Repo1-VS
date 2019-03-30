#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using std::vector;

vector<int> spiralOrder(vector<vector<int>>& matrix)
{
	vector<int> out;
	if (matrix.empty()) return out;

	size_t const rows = matrix.size();
	size_t const cols = matrix[0].size();
	size_t y1 = 0, y2 = rows, x1 = 0, x2 = cols;

	while (1, 1)
	{
		for (size_t x = x1; x != x2; x++)
			out.push_back(matrix[y1][x]);
		y1++;
		if (y1 == y2) return out;
		for (size_t y = y1; y != y2; y++)
			out.push_back(matrix[y][x2 - 1u]);
		x2--;
		if (x1 == x2) return out;
		size_t stop = x1 - 1u;
		for (size_t x = x2 - 1u; x != stop; x--)
			out.push_back(matrix[y2 - 1u][x]);
		y2--;
		if (y1 == y2) return out;
		stop = y1 - 1u;
		for (size_t y = y2 - 1u; y != stop; y--)
			out.push_back(matrix[y][x1]);
		x1++;
		if (x1 == x2) return out;
	}
}


int main()
{
	vector<vector<int>> matrix = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 } };

	vector<int> out = spiralOrder(matrix);
	std::copy(out.begin(), out.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\b\n";
	return 0;
}