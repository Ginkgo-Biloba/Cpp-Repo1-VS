#include <cstdio>

bool canJump(int const* array, int num)
{
	if (num == 1)
		return true;

	int iL = 0, iR = 0;
	for (; iL <= iR; iL++)
	{
		int cur = iL + array[iL];
		if (cur > iR) iR = cur;
		if (iR >= (num - 1)) return true;
	}

	return false;
}

int main()
{
	int const array1[] = { 2, 3, 1, 1, 4 };
	int const array2[] = { 3, 2, 1, 0, 4 };
	int const array3[] = { 2, 0, 0 };

	printf("array1: can%s\n", canJump(array1, sizeof(array1) / sizeof(int)) ? "" : " not");
	printf("array2: can%s\n", canJump(array2, sizeof(array2) / sizeof(int)) ? "" : " not");
	printf("array3: can%s\n", canJump(array3, sizeof(array3) / sizeof(int)) ? "" : " not");
}

