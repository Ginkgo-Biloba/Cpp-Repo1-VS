#include "../src/utility.hpp"


int rangeBitwiseAnd1(int m, int n)
{
	int ans = n;
	for (; (m < n) && ans; ++m)
		ans &= m;
	return ans;
}


int rangeBitwiseAnd2(int m, int n)
{
	int mask = -1; // 0xffffffff;
	for (; (m & mask) != (n & mask); mask <<= 1)
		;
	return m & mask;
}


int rangeBitwiseAnd3(int m, int n)
{
	int shift = 0;
	while (m != n)
	{
		m >>= 1; n >>= 1;
		++shift;
	}
	return m << shift;
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	int ans1 = rangeBitwiseAnd1(10, 11);
	int ans2 = rangeBitwiseAnd2(10, 11);
	int ans3 = rangeBitwiseAnd3(10, 11);
	printf("%1s: %d, %d, %d\n",
		"rangeBitwiseAnd", ans1, ans2, ans3);
}
