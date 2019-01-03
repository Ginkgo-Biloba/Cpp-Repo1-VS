#include <cstdio>
#include <cstdlib>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif
typedef long long llong;

llong strtollong(char* src)
{
	llong x = 0, i = 0, s = 1, t;
	llong up = LLONG_MAX / 10, upt = LLONG_MAX - up * 10;
	llong down = LLONG_MIN / 10, downt = LLONG_MIN - down * 10;
	char c = src[i];
	while (c == ' ' || c == '\t' || c == '\n')
	{ i++; c = src[i]; }
	while (true)
	{
		if (c == '-') s = -s;
		else if (c != '+') break;
		i++; c = src[i];
	}
	while ('0' <= c && c <= '9')
	{
		t = s * (llong)(c - '0');
		if (x > up || (x == up && t > upt))
		{ x = LLONG_MAX; break; }
		else if (x < down || (x == down && t < downt))
		{ x = LLONG_MIN; break; }
		else
		{ x *= 10; x += t; ++i; c = src[i]; }
	}
	return x;
}

int main()
{
	char* src = (char*)(malloc(1024));
	fscanf(stdin, "%1023s", src);
	llong x = strtollong(src);
	fprintf(stdout, "%lld\n", x);
	free(src);
	return 0;
}