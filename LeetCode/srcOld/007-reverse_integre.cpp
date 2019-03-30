#include <cstdio>
#include <cstdlib>
#include <cstring>
#pragma warning (disable: 4996)

/* 用 int64 处理 int32 就是在耍流氓，要不人家让你处理 int64 咋办 */
int reverse(int x)
{
	long long y = 0;
	if (-10 < x && x < 10)
		return x;

	bool pn = (x < 0);
	x = abs(x);
	while (x != 0)
	{
		y *= 10; y += x % 10;
		x /= 10;
	}
	if (pn) y = -y;

	if (y > INT_MAX || y < INT_MIN)
		x = 0;
	else
		x = (int)(y);

	return x;
}

int main()
{
	int x;
	fscanf(stdin, "%d", &x);
	x = reverse(x);
	fprintf(stdout, "%d\n", x);
	return 0;
}

