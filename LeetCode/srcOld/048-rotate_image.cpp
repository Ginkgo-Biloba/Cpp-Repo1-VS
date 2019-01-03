#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#include <crtdbg.h>
#pragma warning(disable: 4996)
#endif

/* 将一个正方形顺时针 in-place 旋转 90 度 */
void rotate(int** matrix, int rows)
{
	int r, c, i, k, val;
	int r2 = rows / 2;

	/* 从外到里，一圈圈旋转 */
	/* (r, c) -> (c, i) -> (i, k) -> (k, r) -> (r, c) */
	for (r = 0; r < r2; r++)
	{
		i = rows - 1 - r;
		for (c = r; c < i; c++)
		{
			k = rows - 1 - c;
			val = matrix[r][c];
			matrix[r][c] = matrix[k][r];
			matrix[k][r] = matrix[i][k];
			matrix[i][k] = matrix[c][i];
			matrix[c][i] = val;
		}
	}
}



int main()
{
	int val = 1, n = 7;
	int r, c;
	int** m = (int**)(malloc(sizeof(*m) * n));
	for (r = 0; r < n; r++)
	{
		m[r] = (int*)(malloc(sizeof(*(m[r])) * n));
		for (c = 0; c < n; c++, val++)
		{
			fprintf(stdout, "%2d ", val);
			m[r][c] = val;
		}
		fprintf(stdout, "\n");
	}

	rotate(m, n);

	for (r = 0; r < n; r++)
		fprintf(stdout, "-=-");
	fprintf(stdout, "\n");
	for (r = 0; r < n; r++)
	{
		for (c = 0; c < n; c++, val++)
		{
			fprintf(stdout, "%2d ", m[r][c]);
		}
		free(m[r]);
		fprintf(stdout, "\n");
	}
	free(m);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}