#include <cstdio>
#include <cstdlib>
#include <cstring>

/* 004 两个有序数组的中位数 */
// https://hk029.gitbooks.io/leetbook
// 这里直接暴力合并吧

int main()
{
	int const n1 = 5;
	int const n2 = 13;
	int const arr1[n1] = { 1, 3, 5 ,5, 7 };
	int const arr2[n2] = { 1, 3, 3, 3, 4, 6, 7, 8, 9, 9, 9, 11, 12 };
	int const kth = ((n1 + n2) >> 1) + 1;
	int* mrg = static_cast<int*>(malloc(sizeof(*mrg) * kth));
	int k = 0, k1 = 0, k2 = 0;
	float median, idx;

	while (k1 < n1 && k2 < n2 && k < kth)
	{
		if (arr1[k1] < arr2[k2])
		{ mrg[k] = arr1[k1]; k1++; }
		else
		{ mrg[k] = arr2[k2]; k2++; }
		k++;
	}
	// arr1 没跑完
	if (k1 < n1 && k < kth)
		memcpy(mrg + k, arr1 + k1, sizeof(int) * (kth - k));
	// arr2 没跑完
	else if (k2 < n2 && k < kth)
		memcpy(mrg + k, arr2 + k2, sizeof(int) * (kth - k));
	else; // 啥都不干

	idx = (n1 + n2 - 1) * 0.5f; // 6 -> 2.5, 7 -> 3
	median = 0.5f * (mrg[static_cast<int>(idx)] + mrg[static_cast<int>(idx + 0.5f)]);
	fprintf(stdout, "%.3f\n", median);
	return 0;
}