#include <cstdio>
#include <cstdlib>
#include <ctime>

/**< 问题 */
// 数组中唯一出现一次的一个，两个，三个数，其余数都是偶数次出现
// Ref: http://www.bubuko.com/infodetail-779766.html

/**< 只出现一次的一个数 */

// 直接全部亦或值就得到了
int find1(int const* arr, int const& n)
{
	int t = arr[0];
	for (int k = 1; k < n; ++k) t ^= arr[k];
	return t;
}

/**< 只出现一次的两个数 */
/* 所有的值亦或肯定不为 0，设最后的抑或结果为 M，找到 M 从低到高为最先为 1 的位置
 * 然后根据所有数在该位置为 0 或者 1，分为两组
 * 这样，两个不同的数就被分到两个不同的组，单独对两个组异或就得到这两个数 */

 // 找到最低位的 1，返回 ...00010... 的形式
int findBit1(int const& k)
{
	// int const sz = sizeof(int); // 在这里是多余的
	// int C = 0;
	// while (((k >> C) & 1) != 1) C++;
	// return C; // 返回所在位数
	return k & (-k);
	// return k & (~(k - 1);
}
int* find2(int const* arr, int const& n)
{
	int* t2 = new int[2];
	t2[0] = t2[1] = 0;
	int t1 = find1(arr, n); // 异或所有数
	int b = findBit1(t1);
	for (int k = 0; k < n; ++k)
		if ((arr[k] & b) != 0)
			t2[0] ^= arr[k];
		else
			t2[1] ^= arr[k];
	return t2;
}

/**< 只出现一次的三个数 */
/* 假定这三个数是 a, b, c, x = a ^ b ^ c (其他的偶数次的都亦或为 0，不管了)
 * 容易证明 x 不与 a, b, c 中的任何一个相等
 * 反证，若 x = a，则 x = a ^ b ^ c 推出 b ^ c = 0, b = c，矛盾，其他同理
 * 且 a ^ x, b ^ x, c ^ x 都不为 0
 * 所以 a ^ x、b ^ x、c ^ x 在 m 处只有一个数字为 1
 * 根据 m = f(a ^ x) ^ f(b ^ x) ^ f(c ^ x) (0000100000形式) 进行分组，首先找到为 1 的那个单独在一组，然后从所有数中排除出去，然后剩下的数组中就剩下两个唯一的数了，用第二种情况就 OK 了。记得所求的是 a^x、b^x、c^x，最后的结果要再亦或一个 x */
int *find3(int const* arr, int const& n)
{
	int const n1 = n - 1;
	int* t3 = new int[3];
	t3[2] = 0; // 其他两个来自 t2，不用提前初始化
	int  x = find1(arr, n); // 异或所有值
	int m = 0;
	int* arrx = new int[n];
	for (int k = 0; k < n; ++k)
	{
		arrx[k] = arr[k] ^ x;
		m ^= findBit1(arrx[k]);
	}
	m = findBit1(m);
	// 根据第 m 位是否为 1，分两组
	for (int k = 0; k < n; ++k)
		if ((arrx[k] & m) != 0)
			t3[2] ^= arrx[k];
	// 移除找出来的那个数
	int* brr = new int[n1];
	for (int k = 0, i = 0; k < n; ++k)
		if (arrx[k] != t3[2])
			brr[i++] = arrx[k];
	int* t2 = find2(brr, n1);
	// 最后异或 x
	t3[0] = t2[0] ^ x; t3[1] = t2[1] ^ x; t3[2] ^= x;
	delete[] arrx; delete[] brr; delete[] t2;
	return t3;
}

// 输出数组
void outArr(int const* arr, int const& n, char const* info)
{
	printf(info);
	for (int k = 0; k < n - 1; ++k)
		printf("%+4d, ", arr[k]);
	printf("%+4d", arr[n - 1]);
}

int main()
{
	int const n = 9;
	int const arr1[n] = { 13, 13, 2, 2, 12, 9, 12, -4, -4 }; // 9
	int const arr2[n + 1] = { 1, 1, -13, 4, 5, 4, -13, 8, 7, 8 }; // 5, 7
	int const arr3[n] = { -2, 3, -14, 5, 6, -14, 1, -2, 3 }; // 1, 5, 6
	outArr(arr1, n, "\nArray 1:\n");
	outArr(arr2, n + 1, "\nArray 2:\n");
	outArr(arr3, n, "\nArray 3:\n");
	int t1 = find1(arr1, n);
	printf("\nOnly 1:\n%4d", t1);
	int* t2 = find2(arr2, n + 1);
	printf("\nOnly 2:\n%4d, %4d", t2[0], t2[1]);
	int* t3 = find3(arr3, n);
	printf("\nOnly 3:\n%4d, %4d, %4d", t3[0], t3[1], t3[2]);
	printf("\n\n");
	delete[] t2; delete[] t3;
	return 0;
}
