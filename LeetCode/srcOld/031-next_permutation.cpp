#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#include <crtdbg.h>
#pragma warning(disable: 4996)
#endif

void nextPermutation(char* str, int const& len)
{
	int q, r; char c;
	if (len <= 1) return;

	/* 从后往前找 str[q - 1] < str[q] */
	/* 没有则说明整个字符串倒序，所以全部反转 */
	for (q = len - 1; q > 0; q--)
	{
		if (str[q - 1] < str[q])
			break;
	}

	/* 找最后一个 r 使得 str[r] > str[q - 1] */
	if (q > 0)
	{
		c = str[q - 1];
		for (r = len - 1; r > q; r--)
		{
			if (str[r] > c)
				break;
		}
		/* 交换 */
		str[q - 1] = str[r]; str[r] = c;
	}

	/* 反转 [q, len - 1] */
	r = len - 1;
	while (q < r)
	{
		c = str[q]; str[q] = str[r]; str[r] = c;
		q++; r--;
	}
}


int main()
{
	char* str = (char*)(malloc(1024));
	fscanf(stdin, "%1023s", str);
	nextPermutation(str, (int)(strlen(str)));
	fprintf(stdout, "%s\n", str);
	free(str);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}

