#include <cstdlib>
#include <cstdio>
#ifdef _MSC_VER
#include <crtdbg.h>
#pragma warning(disable: 4996)
#endif

double pow(double x, int n)
{
	typedef unsigned int uint;
	double ans = 1.0;
	uint un = (uint)(n);
	if (n < 0) un = (uint)(~n) + 1u;
	while (un)
	{
		if (un & 1u) ans *= x;
		un >>= 1; x *= x;
	}
	if (n < 0) ans = 1.0 / ans;
	return ans;
}

int main()
{
	double x, ans; int n;
	fscanf(stdin, "%lf %d", &x, &n);
	ans = pow(x, n);
	if (ans > 1e15 || ans < 1e-15)
		fprintf(stdout, "pow(%f, %d) = %e\n", x, n, ans);
	else
		fprintf(stdout, "pow(%f, %d) = %f\n", x, n, ans);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}