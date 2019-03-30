#include <cstdlib>
#include <cstdio>
#include <climits>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif
typedef long long llong;
typedef unsigned long long ullong;

/* https://segmentfault.com/a/1190000003903492 */
llong div2(llong x, llong y)
{
	llong const ll1 = (llong)(1), ll0 = (llong)(0);
	if (y == ll1) return x;
	if ((y == ll0) || ((x == LLONG_MIN) && (-y == ll1)))
		return LLONG_MAX;

	char ns = 0; /* 负号 */
	if ((x < ll0 && y > ll0) || (x > ll0 && y < ll0))
		ns = 1;
	ullong ux, uy;
	if (x >= ll0) ux = (ullong)(x);
	else { ux = (ullong)(~x); ux++; }
	if (y >= ll0) uy = (ullong)(y);
	else { uy = (ullong)(~y); uy++; }

	ullong ans = (ullong)(0);
	int d = 0;
	while (uy < ux) { uy <<= 1; d++; }

	/* 重置除数，循环 */
	for (; d >= 0; uy >>= 1, d--)
		if (ux >= uy)
		{
			ux -= uy;
			ans |= (ll1 << d); /* += 也行*/
		}

	if (ns) return ((llong)(~ans) + ll1);
	else return (llong)(ans);
}

int main()
{
	llong x, y, z;
	x = LLONG_MIN, y = 2;
	fscanf(stdin, "%lld %lld", &x, &y);
	z = div2(x, y);
	fprintf(stdout, "%lld / %lld = %lld\n", x, y, z);
	return 0;
}