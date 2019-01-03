#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#include <crtdbg.h>
#pragma warning(disable: 4996)
#endif

int jump(int const* A, int const len)
{
	if (len < 2) return 0;
	int ans = 0;
	int pos, next, i;
	i = pos = 0;
	while (pos < len - 1)
	{
		next = pos;
		for (; i <= pos; i++)
			if (next < i + A[i]) next = i + A[i];
		ans++;
		pos = next;
	}
	return ans;
}

int main()
{
	/* 2 3 1 1 4 -> 2*/
	int* A = (int*)(malloc(sizeof(*A) * 100));
	int i, val, len = 0;
	char c;
	while (fscanf(stdin, "%d%c", &val, &c) == 2 && len < 100)
	{
		A[len] = val; len++;
		if (c == '\n') break;
	}

	val = jump(A, len);

	for (i = 0; i < len; i++)
		fprintf(stdout, "%d  ", A[i]);
	fprintf(stdout, "\n%d\n", val);
	free(A);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}