#include <cwchar>
#include <locale>
#include <cstring>
#include <cstdio>

/**< 最长公共子串 (Longest Common Substring) */
// Ref: http://blog.iderzheng.com/longest-common-substring-problem-optimization/

#define preProc \
	int const n1 = (int)(std::wcslen(ws1)); \
	int const n2 = (int)(std::wcslen(ws2)); \
	if (ws1 == nullptr || ws2 == nullptr || n1 == 0 || n2 == 0) return 0; \
	/* 公共字符串对应于原始字符串的起点 */ \
	size_t stt1 = 0; size_t stt2 = 0; \
	/* 最长公共子串的长度 */ \
	size_t maxLen = 0u;  \
	/* 记录比较了多少次 */ \
	int cntCmp = 0

#define outputResult \
	wchar_t* const lcstr = new wchar_t[maxLen + 1]; \
	/* 或者 ws2 从 stt2 开始 maxLen 个字符 */ \
	std::memcpy(lcstr, ws1 + stt1, maxLen * sizeof(wchar_t));  \
	lcstr[maxLen] = L'\0'; \
	wprintf(L"\n\n%s (%d) 和 %s (%d) 的最长子串为: ", ws1, n1, ws2, n2); \
	wprintf(L"%s (%zd)", lcstr, maxLen); \
	wprintf(L"\n共比较 %d 次", cntCmp); \
	delete[] lcstr;

// 暴力解法。时间复杂度 O(N × M × min(N, M))，空间复杂度 O(min(M, N))
size_t lcs1(wchar_t const* ws1, wchar_t const* ws2)
{
	preProc;
	for (int i = 0; i < n1; ++i)
		for (int k = 0; k < n2; ++k)
		{
			size_t len = 0;
			int p = i; int q = k;
			while (p < n1 && q < n2)
			{
				++cntCmp;
				if (ws1[p] != ws2[q]) break;
				++len; ++p; ++q;
			}
			if (maxLen < len)
			{
				maxLen = len;
				stt1 = i; stt2 = k;
			}
		}
	outputResult;
	return maxLen;
}

// 动态规划法。时间复杂度 O(N × M)，空间复杂度 O(N × M)
size_t lcs2(wchar_t const* ws1, wchar_t const* ws2)
{
	preProc;
	// 这样只是为了万一找不到 n1 * n2 字节的连续内存，还能挣扎一下
	size_t** table = new size_t*[n1];
	for (int i = 0; i < n1; ++i)
	{
		table[i] = new size_t[n2];
		std::memset(table[i], 0, n2 * sizeof(size_t));
	}
	// 处理边界
	for (int i = 0; i < n2; ++i)
	{
		++cntCmp;
		table[0][i] = ((ws1[0] == ws2[i]) ? 1 : 0);
	}
	// 比较
	for (int i = 1; i < n1; ++i)
	{
		++cntCmp;
		table[i][0] = ((ws1[i] == ws2[0]) ? 1 : 0);
		for (int k = 1; k < n2; ++k)
		{
			++cntCmp;
			if (ws1[i] == ws2[k])
				table[i][k] = table[i - 1][k - 1] + 1u;
		}
	}
	// 找最大值
	for (int i = 0; i < n1; ++i)
		for (int k = 0; k < n2; ++k)
			if (maxLen < table[i][k])
			{
				maxLen = table[i][k];
				stt1 = i - maxLen + 1;
				stt2 = k - maxLen + 1;
			}
	outputResult;

	for (size_t i = 0; i < n1; ++i)
	{
		delete[] table[i];
		table[i] = nullptr;
	}
	delete[] table;
	return maxLen;
}

// 动态规划法。设 N > M，则时间复杂度 O((N × M)，空间复杂度 O(M)) (选择短的那个在内层循环)
// 这里的实现，如果有多个相同长度的最长公共子串的话，那么只能找到最后一个 (短字符串内)
size_t lcs3(wchar_t const* ws1, wchar_t const* ws2)
{
	preProc;
	// 选最短的一个，存到 ns 和 wss 里面 (short)
	int ns = n1; int nl = n2;
	wchar_t const* wss = ws1; wchar_t const* wsl = ws2;
	if (n1 > n2)
	{
		ns = n2; nl = n1;
		wss = ws2; wsl = ws1;
	}
	size_t* lst = new size_t[nl]; // 起名 list 会惹麻烦
	/* 处理第一行 */
	for (size_t k = 0; k < ns; ++k)
	{
		++cntCmp;
		if (wsl[0] == wss[k])
		{
			lst[k] = 1; maxLen = 1;
			stt1 = k;
		}
		else lst[k] = 0;
	}
	// 其他行
	for (size_t i = 1; i < nl; ++i)
	{
		// 第一个字符
		++cntCmp;
		if (wsl[i] == wss[0])
		{
			lst[0] = 1;
			if (maxLen == 0) { maxLen = 1; stt1 = 0; }
		}
		else lst[0] = 0;
		// 其他的从后往前扫描
		for (size_t k = ns - 1; k > 0; --k)
		{
			++cntCmp;
			if (wsl[i] == wss[k])
			{
				size_t const len = lst[k - 1] + 1u;
				lst[k] = len;
				if (maxLen < len)
				{ maxLen = len; stt1 = k - maxLen + 1; }
			}
			else lst[k] = 0;
		}
	}
	wprintf(L"\n\n%s (%d) 和 %s (%d) 的最长子串为: ", ws1, n1, ws2, n2);
	for (size_t i = 0; i < maxLen; ++i) wprintf(L"%c", wss[stt1 + i]);
	wprintf(L" (%zd)", maxLen);
	wprintf(L"\n共比较 %d 次", cntCmp);

	delete[] lst;
	return maxLen;
}

#undef preProc
#undef outputResult

int main()
{
	setlocale(LC_ALL, "zh-CN");
	wchar_t const* ws1 = L"Invention";
	wchar_t const* ws2 = L"Innovention";
	wchar_t const* ws3 = L"成语：揠苗助长";
	wchar_t const* ws4 = L"宋人揠苗助长的故事";
	lcs1(ws1, ws2);
	lcs2(ws3, ws4);
	lcs3(ws3, ws4);
	wprintf(L"\n");
	return 0;
}
