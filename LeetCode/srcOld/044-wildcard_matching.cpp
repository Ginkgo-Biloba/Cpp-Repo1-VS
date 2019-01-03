#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#include <crtdbg.h>
#pragma warning(disable: 4996)
#endif

bool is_match(char const* s, char const* p)
{
	char const* ast = NULL; /* ast(*) */
	char const* ss = s; /* 字符串 s 中匹配 * 的起始位置 */
	while (*s) /* *s != '\0' */
	{
		/* 当两个字符匹配或者在模式串 p 中发现 ? 时两个指针都前进 */
		/* 注意 *p 不会前行超过长度 */
		if ((*p == '?') || (*p == *s)) { s++; p++; }

		/* 在模式串中 p 发现 *，跟踪 * 的索引，仅仅前行模式串 */
		else if (*p == '*') { ast = p; p++; ss = s; }

		/* 当前字符不匹配，最后一个模式是 *，当前模式指针不是 ast */
		/* 仅仅前行模式串指针 */
		else if (ast) /* ast != nullptr */ { p = ast + 1; ++ss; s = ss; }

		/* 当前模式不是 *，最后一个模式也不是 *，则字符串不匹配 */
		else return false;
	}

	/* 检查模式串中剩余字符 */
	while (*p == '*') p++;

	return !(*p); /* *p == '\0' */
}

int main()
{
	char s[1024], p[1024];
	fscanf(stdin, "%1023s[^ \n]", s);
	fscanf(stdin, "%1023s[^ \n]", p);
	bool ans = is_match(s, p);
	fprintf(stdout, " string || %s\n", s);
	fprintf(stdout, "pattern || %s\n", p);
	fprintf(stdout, " answer || %s\n", (ans ? "true" : "false"));
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}