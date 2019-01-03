#include <wchar.h>
#include <locale>
#include <cstring>
#include <cstdio>

/**< 问题：输入三个字符串 s1、s2、s3，判断第三个字符串 s3 是否由前两个字符串 s1 和 s2 交错而成 */
// Ref: http://taop.marchtea.com/05.04.html
/* 令 dp[i][j] 代表 s3[0...i+j-1] 是否由 s1[0...i-1] 和 s2[0...j-1] 的字符组成。
 * 如果 s1 当前字符 s1[i-1] 等于 s3 当前字符 s3[i+j-1]，而且 dp[i-1][j] 为真，那么可以取 s1 当前字符而忽略 s2，dp[i][j] 返回真；
 * 如果 s2 当前字符等于 s3 当前字符，并且 dp[i][j-1] 为真，那么可以取 s2 而忽略 s1，dp[i][j]返回真；
 * 其它情况，dp[i][j] 返回假。 */
bool isInterleaveDP(wchar_t const* ws1, wchar_t const* ws2, wchar_t const* ws3)
{
	int const len1 = (int)(wcslen(ws1));
	int const len2 = (int)(wcslen(ws2));
	int const len3 = (int)(wcslen(ws3));

	// 长度不一致肯定不对
	if (len1 + len2 != len3)
		return false;
	if (len1 < 0 || len2 < 0 || len3 < 0)
		return false;

	bool** const dp = new bool*[len1 + 1];
	for (int k = 0; k <= len1; ++k)
		dp[k] = new bool[len2 + 1];

	for (int m = 0; m <= len1; ++m)
		for (int n = 0; n <= len2; ++n)
		{
			if ((m == 0 && n == 0)
				|| (m > 0 && dp[m - 1][n] && ws1[m - 1] == ws3[m + n - 1]) // 取 s1
				|| (n > 0 && dp[m][n - 1] && ws2[n - 1] == ws3[m + n - 1])) // 取 s2
				dp[m][n] = true;
			else
				dp[m][n] = false;
		}

	bool rst = dp[len1][len2];
	for (int k = 0; k <= len1; ++k)  delete[] dp[k];
	delete[] dp;
	return rst;
}

// Ref: http://blog.csdn.net/u012804490/article/details/23788355
// 直接扫描
bool isInterleave(wchar_t const* ws1, wchar_t const* ws2, wchar_t const* ws3)
{
	int const len1 = (int)(wcslen(ws1));
	int const len2 = (int)(wcslen(ws2));
	int const len3 = (int)(wcslen(ws3));

	// 长度不一致肯定不对
	if (len1 + len2 != len3)
		return false;
	if (len1 < 0 || len2 < 0 || len3 < 0)
		return false;

	int m = 0; int n = 0; int k = 0;
	while (m < len1 && n < len2 && k < len3)
	{
		if (ws1[m] == ws3[k]) { ++m; ++k; }
		else if (ws2[n] == ws3[k]) { ++n; ++k; }
		else return false;
	}
	while (m < len1 && k < len3) // s1 有剩余
	{
		if (ws1[m] == ws3[k]) { ++m; ++k; }
		else return false;
	}
	while (n < len2 && k < len3) // s2 有剩余
	{
		if (ws2[n] == ws3[k]) { ++n; ++k; }
		else return false;
	}

	// 终于到头了也没有意外
	return true;
}

int main()
{
	setlocale(LC_ALL, "zh-CN");
	wchar_t const* str1 = L"今天好天气";
	wchar_t const* str2 = L"是个啊";
	wchar_t const* str3 = L"今天是个好天气啊";
	bool rst = isInterleave(str1, str2, str3);
	wprintf(L"\n字符串 1：%s", str1);
	wprintf(L"\n字符串 2：%s", str2);
	wprintf(L"\n字符串 3：%s", str3);
	wprintf(L"\n交替字符串：%s", (rst ? L"是" : L"否"));
	wprintf(L"\n");
	return 0;
}
