#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

int main()
{
	char* src, *dst;
	int i, j, m;
	src = (char*)(malloc(1024));
	dst = (char*)(malloc(1024));
	fscanf(stdin, "%1023s", src);
	fscanf(stdin, "%d", &m);

	int len = (int)(strlen(src));

	if (len < 2 || m < 2)
		memcpy(dst, src, len + 1);
	else
	{
		int c = 0, n = 2 * m - 2;
		for (j = 0; j < len; j += n)
			dst[c++] = src[j];
		for (i = 1; i < m - 1; i++)
			for (j = 0; j < len; j += n)
			{
				if (i + j < len)
					dst[c++] = src[i + j];
				if (j + n - i < len)
					dst[c++] = src[j + n - i];
			}
		for (j = m - 1; j < len; j += n)
			dst[c++] = src[j];
		dst[c] = '\0';
	}

	fprintf(stdout, "%s\n", dst);
	free(src); free(dst);
	return 0;
}