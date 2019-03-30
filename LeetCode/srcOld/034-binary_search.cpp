#include <cstdio>
#include <cstdlib>
#include <cstring>

/* 二分查找
 * Ref: https://www.zhihu.com/question/36132386
 * 以下区间均为左闭右开区间 */

/* 下界：求最小的 idx，使得 a[idx] >= key */
int lowerBound(int const* a, int const& n, int const& key)
{
	if (a[0] >= key) return 0;
	if (a[n - 1] < key) return -1; /* 看要求，或者返回 n */
	int iL = 0; int iR = n - 1; /* [0, n - 1] */;
	int iM;
	while (iL < iR)
	{
		iM = iL + ((iR - iL) >> 1); /* 向下取整 */
		if (a[iM] < key) iL = iM + 1;
		else iR = iM;
	}
	return iL; /* iR 也可，因为最后 iL == iR */
}

/* 上界：求最小的 idx，使得 a[idx] > key */
int upperBound(int const* a, int const& n, int const& key)
{
	if (a[0] > key) return 0;
	if (a[n - 1] <= key) return -1; /* 看要求，或者返回 n */
	int iL = 0; int iR = n - 1; /* [1, n - 1] */;
	int iM;
	while (iL < iR)
	{
		iM = iL + ((iR - iL) >> 1); /* 向下取整 */
		if (a[iM] <= key) iL = iM + 1;
		else iR = iM;
	}
	return iR; /* iL 也可，因为最后 iL == iR */
}

void outArr(int const* arr, int const& n, char const* info)
{
	printf(info);
	for (int k = 0; k < n - 1; ++k)
		printf("%2d, ", arr[k]);
	printf("%2d", arr[n - 1]);
}

int main()
{
	int const n = 7;
	int const a[n] = { 1, 1, 3, 5, 5, 8, 8 };
	outArr(a, n, "\nArray A: ");
	printf("\nlower bound (5): %d", lowerBound(a, n, 5));
	printf("\nupper bound (5): %d", upperBound(a, n, 5));
	printf("\n");
	return 0;
}
