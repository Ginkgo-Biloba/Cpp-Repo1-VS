#include "../srcOld/utility.hpp"

class NumMatrix
{
public:
	// 真的积分图了，参考经典的 boxFilter
	vector<int> acc;
	int rows, cols;

	int idx(int r, int c)
	{
		return r * (cols + 1) + c;
	}

	NumMatrix(vector<vector<int>> const &matrix)
	{
		rows = static_cast<int>(matrix.size());
		if (rows == 0)
			return;
		cols = static_cast<int>(matrix[0].size());

		size_t need = static_cast<size_t>(rows + 1) * (cols + 1);
		if (acc.size() < need)
			acc.resize(need);
		memset(acc.data(), 0, sizeof(int) * (cols + 1));

		for (int r = 0; r < rows; ++r)
		{
			int const* M = matrix[r].data();
			int* A = &(acc[idx(r + 1, 1)]);
			int* Aprev = &(acc[idx(r, 1)]);
			int line = 0;
			A[-1] = 0;
			for (int c = 0; c < cols; ++c)
			{
				line += M[c];
				A[c] = line + Aprev[c];
				printf("%4d ", A[c]);
			}
			printf("\n");
		}
	}

	int sumRegion(int r1, int c1, int r2, int c2)
	{
		return acc[idx(r2 + 1, c2 + 1)]
			- acc[idx(r2 + 1, c1)] - acc[idx(r1, c2 + 1)]
			+ acc[idx(r1, c1)];
	}
};


int main()
{
	vector<vector<int>> matrix =
	{
		{ 3, 0, 1, 4, 2 },
		{ 5, 6, 3, 2, 1 },
		{ 1, 2, 0, 1, 5 },
		{ 4, 1, 0, 1, 7 },
		{ 1, 0, 3, 0, 5 },
	};

	NumMatrix nm(matrix);
	printf("%d\n", nm.sumRegion(2, 1, 4, 3));
}
