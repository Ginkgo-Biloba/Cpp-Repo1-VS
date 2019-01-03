#include "../src/utility.hpp"

vector<vector<int>> generateMatrix(int n)
{
	vector<vector<int>> mat(n);
	if (!n)
		return mat;
	else if (n == 1)
	{
		mat[0].push_back(1);
		return mat;
	}
	else
	{
		for (int i = 0; i < n; i++)
			mat[i].resize(n);
	}

	int num = 1;
	int x1 = 0, x2 = n, y1 = 0, y2 = n;
	while (1)
	{
		for (n = x1; n < x2; n++)
			mat[y1][n] = num++;
		y1++;
		if (y1 == y2) break;
		for (n = y1; n < y2; n++)
			mat[n][x2 - 1] = num++;
		x2--;
		if (x1 == x2) break;
		for (n = x2 - 1; n >= x1; n--)
			mat[y2 - 1][n] = num++;
		y2--;
		if (y2 == y1) break;
		for (n = y2 - 1; n >= y1; n--)
			mat[n][x1] = num++;
		x1++;
		if (x1 == x2) break;
	}

	return mat;
}


int main()
{
	vector<vector<int>> grid = generateMatrix(4);
	output(grid, "generateMatrix");
}
