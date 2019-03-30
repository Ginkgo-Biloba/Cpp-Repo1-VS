#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

int dict(char c)
{
	int x = 0;
	if (c == 'I') x = 1;
	else if (c == 'V') x = 5;
	else if (c == 'X') x = 10;
	else if (c == 'L') x = 50;
	else if (c == 'C') x = 100;
	else if (c == 'D') x = 500;
	else if (c == 'M') x = 1000;
	return x;
}

int roman2int(char* r)
{
	int len = (int)(strlen(r));
	int ans = 0, i = 0, x;
	while (i < len)
	{
		x = dict(r[i]);
		if (i < len - 1 && x < dict(r[i + 1]))
		{
			ans -= x; ans += dict(r[i + 1]);
			i += 2;
		}
		else
		{
			ans += x;
			i++;
		}
	}
	return ans;
}

int main()
{
	int x;
	char* r = (char*)(malloc(256));
	fscanf(stdin, "%255s", r);
	x = roman2int(r);
	fprintf(stdout, "%d\n", x);
	free(r);
	return 0;
}