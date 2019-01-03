#include <cstdio>
#include <cstdlib>
#include <ctime>

// Ref: http://blog.chinaunix.net/uid-26456800-id-3512430.html
/* 长度为 n 的数组乱序存放着 0 至 n-1，现在只能进行 0 与其他数的交换，请设计并实现排序 */
/* 2 个 key：
一个是只能与 0 交换，另一个是数组的下标和值是一一对应的。
第二个容易被忽略。所以读到一个元素时，如果值和下标不等，那么可以直接把这个元素的值放到正确位置上去，目标位置的值挪回来。当然这个过程要借助元素0来完成。
假设输入是 2,0,3,1；
step 1：遍历数组，找出值为 0 的元素，和 num[0] 交换：
0 2 3 1；
step 2：如果 num[1] 下标和值匹配，考虑下一个，否则尝试把 num[1] 的值借助 num[0] 放入正确的位置
3 2 0 1 -->  3 0 2 1 --> 0 3 2 1；
step 3：重复 step 2，直到 num[1] 正确被放置了 1；
step 4：num[1] 处理完，step2 处理下一个元素 num[2]，直到所有元素的位置和值都匹配 */

void xch(int* pa, int* pb)
{
	int t = *pa; *pa = *pb; *pb = t;
}

int main()
{
#define FOR(k, n) for(k = 0; k < n; ++k)
	int const n = 20;
	int arr[n];
	srand(static_cast<unsigned>(time(nullptr)));
	int k;
	FOR(k, n) arr[k] = k;
	FOR(k, n) xch(arr + k, arr + rand() % n);
	printf("\n----- Array -----\n");
	FOR(k, n - 1) printf("%d, ", arr[k]);
	printf("%d", arr[n - 1]);

	// 找到 0
	FOR(k, n) if (arr[k] == 0)
	{
		xch(arr, arr + k);
		break;
	}
	k = 1;
	while (k < n)
	{
		if (arr[k] == k) ++k;
		else
		{
			int const t = arr[k];
			xch(arr, arr + t); // 把 0 移到 arr[k] 的目标位置
			xch(arr + t, arr + k);
			xch(arr, arr + k); // 移回 0
		}
	}

	printf("\n----- Sorted -----\n");
	FOR(k, n - 1) printf("%d, ", arr[k]);
	printf("%d", arr[n - 1]);
	printf("\n\n");
	return 0;
#undef FOR
}
