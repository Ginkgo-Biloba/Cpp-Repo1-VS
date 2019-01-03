#include <cstdio>
#include <cstdlib>
#include <ctime>

/**< 荷兰国旗问题 */
/* Ref: http://taop.marchtea.com/02.07.html
* 这个问题类似快排中 partition 过程，只是需要用到三个指针
* 一个前指针 begin、一个中指针 current、一个后指针 end。current 指针遍历整个数组序列，当
* 1 current 指针所指元素为 0 时，与 begin 指针所指的元素交换，而后 current++，begin++ ；
* 2 current 指针所指元素为 1 时，不做任何交换（即球不动），而后 current++；
* 3 current 指针所指元素为 2 时，与 end 指针所指的元素交换，而后，current 指针不动，end-- 。*/

// 交换
void xch(int* pa, int* pb)
{
	int t = *pa; *pa = *pb; *pb = t;
}

void df(int* arr, int n)
{
	int ib = 0; int ic = 0; int ie = n - 1;
	while (ic <= ie)
		switch (arr[ic])
		{
		case 0:
			xch(arr + ib, arr + ic);
			++ib; // ++ic; break; // 看 case 1 会发现这个是多余的
		case 1:
			++ic; break;
		case 2:
			xch(arr + ic, arr + ie);
			--ie; break;
		}
}

int main()
{
	int const n = 25;
	int const p1 = 0x2fff; int const p2 = 0x5fff;
	int arr[n];
	srand(static_cast<unsigned>(time(nullptr)));
	printf("\nArray:\n");
	for (int k = 0; k < n; ++k)
	{
		int t = rand();
		if (t < p1)  t = 0;
		else if (t < p2)  t = 1;
		else t = 2;
		arr[k] = t; printf("%d  ", t);
	}
	df(arr, n);
	printf("\n\nRe-assigned:\n");
	for (int k = 0; k < n; ++k) printf("%d  ", arr[k]);
	printf("\n");
	return 0;
}
