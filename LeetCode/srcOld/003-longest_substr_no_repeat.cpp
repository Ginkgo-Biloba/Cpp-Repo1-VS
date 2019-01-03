#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

/* 003 求一个字符串中最长的没有重复字符的子串 */
// http://www.cnblogs.com/luxiaoxun/archive/2012/10/02/2710471.html

int main()
{
	char* str = (char*)(malloc(41));
	char* rst = (char*)(malloc(41));
	memset(rst, 0, 41);
	fscanf(stdin, "%40[^\n]%*c", str);
	int const len = static_cast<int>(strlen(str));
	if (len < 1)
		return 1;

	int iB = 0, iLen = 1, idx = 0, d;
	for (int i = 1; i < len; i++)
	{
		char c = str[i];
		int j;
		for (j = i - 1; j >= idx; j--) // 遍历到上一次最长子串开始位置
		{
			if (str[j] == c)
				break;
		}
		idx = j + 1; // 从 i 往前只能到这里了
		d = i - j; // i - idx + 1; // 长度
		if (iLen < d)
		{ iLen = d; iB = idx; }
	}

	memcpy(rst, str + iB, iLen);
	rst[iLen] = '\0';
	fprintf(stdout, "字符串 || %s\n", str);
	fprintf(stdout, "不重复 (%d)[%d -> %d) || %s\n", iLen, iB, iB + iLen, rst);

	free(str); free(rst);
	return 0;
}