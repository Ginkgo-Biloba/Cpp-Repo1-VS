#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#include <crtdbg.h>
#pragma warning(disable: 4996)
#endif

/* 用栈 */
int lvp_stack(char* str)
{
	int len = (int)(strlen(str));
	int i, prev = -1, cur, ans = 0;
	if (len == 0) return ans;
	int* stack = (int*)(malloc(sizeof(int) * len)); /* 左括号位置 */
	int sd = 0; /* 栈的深度 */

	for (i = 0; i < len; i++)
	{
		if (str[i] == '(')
		{ stack[sd] = i; sd++; }
		else /* if str[i] == ')') */
		{
			if (sd > 0) /* 有左括号 */
			{
				sd--;
				if (sd == 0) cur = i - prev; /* ()|() 连接前面的合法序列 */
				else cur = i - stack[sd - 1];
				if (ans < cur) ans = cur;
			}
			/* 这个 ) 不构成合法序列，下次从下一个字符算起 */
			else prev = i;
		}
	}

	free(stack);
	return ans;
}

/* 用动态规划 */
int lvp_dp(char const* str)
{
	int len = (int)(strlen(str));
	int i, j, ans = 0;
	if (len == 0) return ans;
	/* dp[i] 为 [str[0], str[i]] 的合法序列长度 */
	int* dp = (int*)(malloc(sizeof(*dp) * len));
	memset(dp, 0, sizeof(*dp) * len);

	for (i = 1; i < len; i++)
		if (str[i] == ')')
		{
			if (str[i - 1] == '(') /* 一对 () 与前面的连着 */
			{
				if (i >= 2) dp[i] = dp[i - 2] + 2;
				else dp[i] = 2;
			}
			else /* str[i - 1] == ')*/
			{
				j = i - dp[i - 1] - 1;
				if (j >= 0 && str[j] == '(')
				{
					dp[i] = dp[i - 1] + 2;
					if (j - 1 >= 0) dp[i] += dp[j - 1]; /* 加上前面的序列 */
				}
			}
			if (ans < dp[i]) ans = dp[i];
		}

	free(dp);
	return ans;
}


int main()
{
	char* str = (char*)(malloc(1024));
	fscanf(stdin, "%1023s", str);
	int ans_stack = lvp_stack(str);
	int ans_dp = lvp_dp(str);
	fprintf(stdout, "%d,  %d\n", ans_stack, ans_dp);
	free(str);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}