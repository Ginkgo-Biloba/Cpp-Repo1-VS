#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

static const char* letters[4][10] = { \
{ "","I","II","III","IV","V","VI","VII","VIII","IX" },
{ "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" },
{ "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" },
{ "","M","MM","MMM" } };

/* [1, 3999] */
void int2roman(int x, char* r)
{
	int c, s;
	c = x / 1000 % 10; s = (int)(strlen(letters[3][c]));
	memcpy(r, letters[3][c], s); r += s;
	c = x / 100 % 10; s = (int)(strlen(letters[2][c]));
	memcpy(r, letters[2][c], s); r += s;
	c = x / 10 % 10; s = (int)(strlen(letters[1][c]));
	memcpy(r, letters[1][c], s); r += s;
	c = x % 10; s = (int)(strlen(letters[0][c]));
	memcpy(r, letters[0][c], s); r += s;
	*r = '\0';
}

int main()
{
	int x;
	char* r = (char*)(malloc(1024));
	fscanf(stdin, "%d", &x);
	int2roman(x, r);
	fprintf(stdout, "%s\n", r);
	free(r);
	return 0;
}