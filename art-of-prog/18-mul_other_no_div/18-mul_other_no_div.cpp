#include <cstdio>
#include <cstdlib>
#include <ctime>

// Ref: http://taop.marchtea.com/02.15.html
/* 不用除法运算
 * 两个数组 a[N], b[N]，其中 a[N] 的各个元素值已知，现给 b[i] 赋值，b[i] = a[0] * a[1] * a[2] * ... * a[N-1] / a[i]
 * 1 不准用除法运算
 * 2 除了循环计数值，a[N], b[N]外，不准再用其他任何变量，包括局部变量，全局变量等
 * 3 满足时间复杂度 O(n)，空间复杂度 O(1)。
 * 题目相当于求 b[i] = a[0] * a[1] * a[2] * a[3] * ... * a[i-1] * a[i+1] * ... * a[N-1]
 * 等价于除掉当前元素 a[i]，其他所有元素 (a[i] 左边部分和右边部分) 的积。
 * 记 left[i]=∏a[k], (k=1...i-1); right=∏a[k], (k=i+1...n)，根据题目描述 b[i] = left[i] * right[i]
 * 对于每一个 b[i] 初始化为1，left[i] 和right[i] 两部分可以分开两次相乘
 * 即对于循环变量 i = 1...n, b[i] = left[i]; b[n-i] = right[n-i]。循环完成时即可完成计算。*/
void noDivision(int const* arr, float* brr, int const& n)
{
	int const n1 = n - 1;
	int left = 1; int right = 1;
	for (int k = 0; k < n; ++k) brr[k] = 1.0f;
	for (int k = 0; k < n; ++k)
	{
		brr[k] *= left;
		brr[n1 - k] *= right;
		left *= arr[k];
		right *= arr[n1 - k];
	}
}

int main()
{
	int const n = 10;
	int arr[n]; float brr[n];
	srand(static_cast<unsigned>(time(NULL)));
	printf("\nArray:\n");
	for (int k = 0; k < n; ++k)
	{
		int const m = rand() / 0x7ff + 1;
		arr[k] = m; printf("%8d  ", m);
	}
	noDivision(arr, brr, n);
	printf("\n\nNo division:\n");
	for (int k = 0; k < n; ++k) printf("%.0f  ", brr[k]);
	printf("\n\n");
	return 0;
}
