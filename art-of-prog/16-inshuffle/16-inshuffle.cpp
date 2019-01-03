#include <cstdio>
#include <cstring>

/**< 完美洗牌算法 */
// Ref: http://taop.marchtea.com/02.09.html

// 位置置换，时间空间均为 O(N)
// i -> (2 * i + 1) % n: i -> (2 * i + 1), i -> (2 * i + 1) - (n + 1)
void shuffle1(int* arr, int const&n)
{
	if (n & 1) return;
	int* brr = new int[n];
	int const nDiv2 = n / 2;
	for (int k = 0; k < nDiv2; ++k) brr[k * 2 + 1] = arr[k];
	for (int k = nDiv2; k < n; ++k) brr[k * 2 - n] = arr[k];
	memcpy(arr, brr, n * sizeof(int));
	delete[] brr;
}

int main()
{
	int const n = 10;
	int arr[n];
	printf("\nArray:\n");
	for (int k = 0; k < n; ++k) { arr[k] = 1 + k; printf("%d  ", 1 + k); }
	shuffle1(arr, n);
	printf("\n\nShuffled Array:\n");
	for (int k = 0; k < n; ++k)
		printf("%d  ", arr[k]);
	printf("\n\n");
	return 0;
}
