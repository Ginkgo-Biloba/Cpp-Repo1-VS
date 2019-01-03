#include <cstring>
#include <cstdio>
#include <cstdlib>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

/* 看看括号合不合法。{} () [] 合法，(] [} {] 这种不合法 */
bool isValid(char const* str)
{
	size_t i, s = 0u, len = strlen(str);
	char* stack = (char*)(malloc(len));
	char c, d; bool is = true;
	for (i = 0u; i < len; i++)
	{
		c = str[i];
		if (c == '(' || c == '[' || c == '{')
		{ stack[s] = c; s++; }
		else
		{
			s--; d = stack[s];
			if ((c == ')' && d != '(') \
				|| (c == ']' && d != '[') || (c == '}' && d != '{'))
			{ is = false; break; }
		}
	}
	if (s != 0) is = false;
	free(stack);
	return is;
}


int main()
{
	char* str = (char*)malloc(1024);
	fscanf(stdin, "%1023s", str);
	fprintf(stdout, "%s\n", (isValid(str) ? "Yes" : "No"));
	free(str);
	return 0;
}