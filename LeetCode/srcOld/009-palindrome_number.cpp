#include <cstdio>
#include <cstdlib>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

/* 一个数是否是回文数，不用额外空间？ */
bool isPalindrome(int x)
{
	if (x < 0) return false; /* 负数不回文？*/
	if (x < 12) return true; /* 一个数字肯定回文 */

	int r = 0, y = x;
	while (y != 0)
	{
		r *= 10; r += y % 10; /* 不用管溢出，溢出了肯定不回文 */
		y /= 10;
	}
	return (r == x);
}

/* LeetCode 上的 */
bool isPalindrome2(int x)
{
	/* 负数不回文。如果最末位数是 0，那么必须开头也是 0 才行，只有 0 */
	if (x < 0 || (x % 10 == 0 && x != 0))
		return false;

	int r = 0;
	while (x > r)
	{
		r *= 10; r += x % 10;
		x /= 10;
	}

	/* 如果长度是奇数，那么 r / 10 可以丢掉中间的数字 */
	/* 例如输入是 12321, 那么循环结束时 x = 12, r = 123 */
	return (x == r || x == r / 10);
}

int main()
{
	int x;
	fscanf(stdin, "%d", &x);
	fprintf(stdout, "%s\n", (isPalindrome(x) ? "Yes" : "No"));
	return 0;
}