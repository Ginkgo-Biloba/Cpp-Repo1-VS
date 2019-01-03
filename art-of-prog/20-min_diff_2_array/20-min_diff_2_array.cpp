#include <cstdio>
#include <cmath>

// Ref: https://my.oschina.net/u/1470003/blog/266255
/* 有两个序列 a、b，大小都为 n，序列元素的值任意整数，无序
 * 要求通过交换 a、b 中的元素，使「a 元素的和」与「 b 元素的和」之间的差 (这里指绝对值) 最小
 * 对于序列 a 和 b，令A = sum(a) - sum(b)。
 * 分别用 i、j 遍历 a、b序列，若 a[i] 和 b[j] 交换，则
 * A' = sum(a) - a[i] + b[j] - (sum(b) - b[j] + a[i] = sum(a) - sum(b) - 2(a[i] - b[j]) = A - 2(a[i] - b[j]) = A - 2x
 * 即 (a[i] - b[j]) 在(0, A) 之间并且最接近 A / 2 则序列 a、b 的差值最小
 * 因此在 a 和 b 中寻找使得 x 在 (0, A) 之间并且找到最接近 A/2 的 i 和 j，交换相应的元素，重新计算 A 后，重复前面的步骤，直至找不到 (0, A) 之间的 x 为止。*/

void xch(int* const pa, int* const pb)
{
	int t = *pa; *pa = *pb; *pb = t;
}

void outArr(int const* arr, int const& n, char const* info)
{
	printf(info);
	for (int k = 0; k < n - 1; ++k)
		printf("%+4d, ", arr[k]);
	printf("%+4d", arr[n - 1]);
}

void minDiff(int* arr, int* brr, int const& n)
{
#define FOR(k, n) for(int (k) = 0; (k) < n; ++(k))
	int A = 0;
	FOR(i, n) A += arr[i];
	FOR(i, n) A -= brr[i];
	if (A == 0)  return; // 相等

	outArr(arr, n, "\n\n----- Orignal ------\nArray A: ");
	outArr(brr, n, "\nArray B: ");
	printf("\nDifference (A - B): %d", A);
	int si = 0; int sj = 0; // 记住要交换的索引
	while (true)
	{
		int const ADiv2 = A / 2;
		int th = abs(ADiv2); int x = 0;
		FOR(i, n)
			FOR(j, n)
		{
			int const xin = arr[i] - brr[j];
			int const xinTh = abs(xin - ADiv2);
			if (xinTh < th) // x 肯定在 0，A 之间
			{
				th = xinTh; x = xin;
				si = i; sj = j;
			}
		}
		if (x != 0) // 有可交换的
		{
			xch(arr + si, brr + sj);
			A -= 2 * x;
		}
		else break;
	}

	outArr(arr, n, "\n\n----- After exchanging -----\nArray A: ");
	outArr(brr, n, "\nArray B: ");
	printf("\nDifference (A - B): %d", A);
	/*A = 0; // 验算一下
	FOR(i, n) A += arr[i];
	FOR(i, n) A -= brr[i];
	printf("\nDifference: %d", A);*/
#undef FOR
}

int main()
{
	int const n = 7;
	int arr[n] = { -4, 44, 34, 7, 21, 56, 27 };
	int brr[n] = { 23, 12, -13, 12, 24, -39, -31 };
	minDiff(arr, brr, n);
	printf("\n\n");
	return 0;
}
