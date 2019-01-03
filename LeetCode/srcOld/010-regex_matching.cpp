#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

bool isMatch(char* text, char* pattern)
{
	int lt = (int)(strlen(text)), lp = (int)(strlen(pattern));
	if (lp == 0) return (lt == 0);

	/* dp[t][p] 表示 text[t:] 和 ptn[p:] 是否匹配 */
	int t, p;
	char** dp = (char**)(malloc(sizeof(char*) * (lt + 1)));
	for (t = 0; t <= lt; t++)
	{
		dp[t] = (char*)(malloc(lp + 1));
		memset(dp[t], 0, lp + 1);
	}
	dp[lt][lp] = 1; /* 末尾 '\0' 认为匹配，可以不考虑右边界 */
	char firstMatch = 1; /* 初始为 1，根据短路规则，后面 t 和 p 不会越界 */

	for (t = lt; t >= 0; t--)
		for (p = lp - 1; p >= 0; p--)
		{
			firstMatch = (t < lt && (text[t] == pattern[p] || pattern[p] == '.'));
			/* A* 匹配 空 或 A */
			if (p + 1 < lp && pattern[p + 1] == '*')
				dp[t][p] = (dp[t][p + 2] || (firstMatch && dp[t + 1][p]));
			/* A 匹配 A */
			else dp[t][p] = (firstMatch && dp[t + 1][p + 1]);
		}

	firstMatch = dp[0][0];
	for (t = 0; t <= lt; t++) free(dp[t]);
	free(dp);
	return (firstMatch == 1);
}

int main()
{
	char* text = (char*)(malloc(1024)); text[0] = '\0';
	char* pattern = (char*)(malloc(1024));
	while (text[0] != 'q' || pattern[0] != 'q')
	{
		fscanf(stdin, "%1023s %1023s", text, pattern);
		fprintf(stdout, "%s\n", (isMatch(text, pattern) ? "Yes" : "No"));
	}
	return 0;
}