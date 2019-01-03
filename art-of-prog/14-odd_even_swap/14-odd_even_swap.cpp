#include <cstdio>
#include <cstdlib>
#include <ctime>

/**< 奇偶调序 */
// Ref: http://taop.marchtea.com/02.06.html
// 输入一个整数数组，调整数组中数字的顺序，使得：
// 所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。
// 要求时间复杂度为O(N)

// 交换
void xch(int* pa, int* pb)
{
	int t = *pa; *pa = *pb; *pb = t;
}

// 两端指针，不稳定，复杂度 O(N)
void oex1(int* arr, int const& n)
{
	int b = 0; int e = n - 1;
	while (true)
	{
		while ((arr[b] & 1) && b < e)  ++b; // 奇数
		while (!(arr[e] & 1) && b < e)  --e; // 偶数
		if (b < e) xch(arr + b, arr + e);
		else break;
	}
}

// 前后指针，奇数稳定，复杂度 O(N)
void oex2(int* arr, int const& n)
{
	int b = 0; int e = 1;
	while (true)
	{
		while (!(arr[e] & 1) && e < n) ++e; // 前指针，跳过偶数
		while ((arr[b] & 1) && b < n) ++b; // 后指针，跳过奇数
		if (b < e && e < n) xch(arr + b, arr + e);
		else break;
	}
}

// 稳定正负调序，复杂度不满足 O(N^2)
void npx(int* arr, int const& n)
{
	int e = n - 1;
	while (e > 0 && arr[e] >= 0) --e; // 0 视为正数
	int b = e - 1;
	for (; b >= 0; --b)
	{
		if (arr[b] < 0) continue;
		int t = arr[b];
		for (int i = b; i < e; ++i)
			arr[i] = arr[i + 1];
		arr[e] = t;
		--e;
	}
}

int main()
{
	int const n = 20;
	int arr[n];
	srand(static_cast<unsigned>(time(NULL)));
	printf("\nArray:\n");
	for (int k = 0; k < n; ++k)
	{
		int const m = rand();
		arr[k] = m; printf("%6d  ", m);
	}
	oex2(arr, n);
	printf("\n\noex2:\n");
	for (int k = 0; k < n; ++k)
		printf("%6d  ", arr[k]);

	printf("\n\nArray:\n");
	for (int k = 0; k < n; ++k)
	{
		int const m = rand() - 0x3fff;
		arr[k] = m; printf("%6d  ", m);
	}
	npx(arr, n);
	printf("\n\nnpx:\n");
	for (int k = 0; k < n; ++k)
		printf("%6d  ", arr[k]);
	printf("\n\n");
	return 0;
}
