#include <cstdio>
#include <cstring>
#include <cwchar>
#include <locale>

/**< 问题：字符串编辑距离 */
// Ref: http://taop.marchtea.com/05.02.html

int EditDistance(wchar_t const* src, wchar_t const* dst)
{
	int m, n, k;
	int const sL = (int)(wcslen(src));
	int const dL = (int)(wcslen(dst));
	int** const dp = new int*[sL + 1];
	for (k = 0; k <= sL; ++k)
		dp[k] = new int[dL + 1];
	// 边界
	dp[0][0] = 0;
	for (m = 1; m <= sL; ++m)
		dp[m][0] = m;
	for (n = 1; n <= dL; ++n)
		dp[0][n] = n;
	for (m = 1; m <= sL; ++m)
		for (n = 1; n <= dL; ++n)
		{
			if (src[m - 1] == dst[n - 1])
				dp[m][n] = dp[m - 1][n - 1];
			else
			{
				dp[m][n] = dp[m - 1][n - 1];
				if (dp[m][n] > dp[m - 1][n]) dp[m][n] = dp[m - 1][n];
				if (dp[m][n] > dp[m][n - 1]) dp[m][n] = dp[m][n - 1];
				dp[m][n] += 1;
			}
		}

	m = dp[sL][dL];
	// 清理
	for (k = 0; k <= sL; ++k)
		delete[] dp[k];
	delete[] dp;
	return m;
}

int main()
{
	setlocale(LC_ALL, "zh-CN");
	wchar_t const* str1 = L"绿树荫浓夏日长";
	wchar_t const* str2 = L"悠悠夏木啭黄鹂";
	int dist = EditDistance(str1, str2);
	wprintf(L"\n字符串 1：%s", str1);
	wprintf(L"\n字符串 2：%s", str2);
	wprintf(L"\n编辑距离：%d", dist);
	wprintf(L"\n");
	return 0;
}
