#include <cwchar>
#include <locale>
#include <cstring>
#include <cstdio>

/**< 后缀数组 (Suffix Array) */

// 倍增算法（Prefix Doubling）
// Ref: https://zhuanlan.zhihu.com/p/21283102
// Ref: http://www.cnblogs.com/chengxuyuancc/p/3306963.html
void pd(wchar_t const* ws, size_t n)
{
	if (ws == nullptr || n < 2) return;
	size_t const n1 = n - 1;
	size_t const sup = ((static_cast<size_t>(1)) << (8 * sizeof(wchar_t))); // 上界，wchar_t 最大值 + 1
	size_t* SA = new size_t[n];
	std::memset(SA, 0, n * sizeof(size_t));
	wchar_t* const wsd = new wchar_t[n + 1];
	std::memcpy(wsd, ws, n * sizeof(wchar_t));
	wsd[n] = L'\0';

	// 分配基数排序的“桶”
	size_t* const bucket = new size_t[sup];
	size_t* x = new size_t[n]; // 上次基数
	size_t* y = new size_t[n]; // 这次基数
	/* 对后缀的第一个字符（字符串中所有单个字符）进行基数排序 */
	for (size_t i = 0; i < sup; ++i) bucket[i] = 0;
	for (size_t i = 0; i < n; ++i) { x[i] = ws[i]; ++bucket[ws[i]]; }
	for (size_t i = 1; i < sup; ++i) bucket[i] += bucket[i - 1];
	for (size_t i = n1; i != (size_t)(-1); --i) SA[--bucket[x[i]]] = i;

	size_t m = sup; // m 表示当前名次的最大值
	for (size_t k = 1; k <= n; k <<= 1) // 倍增
	{
		// 对第二关键字排序，利用了上一次的结果
		size_t p = 0;
		// y[i] 用来表示名次为 i 的后缀(j + k) 的 j 。接下来直接用 SA 对第二关键字排序
		// 后缀 n - k 及之后的所有后缀第二关键字最小
		for (size_t i = n - k; i < n; ++i) y[p++] = i;
		// SA[i] >= k 表示该后缀出现在 k 之后，那么就是第二关键字，且因为 SA 已排序好，这样便可以通过这个排序出第二关键字
		for (size_t i = 0; i < n; ++i)
			if (SA[i] >= k) y[p++] = SA[i] - k;
		// 第一关键字排序
		for (size_t i = 0; i < m; ++i) bucket[i] = 0;
		for (size_t i = 0; i < n; ++i) ++bucket[x[y[i]]];
		for (size_t i = 1; i < m; ++i) bucket[i] += bucket[i - 1];
		for (size_t i = n1; i != (size_t)(-1); --i) SA[--bucket[x[y[i]]]] = y[i];
		// 交换 x 和 y，为了重复利用空间
		size_t* xy = x; x = y; y = xy;
		p = 1; x[SA[0]] = 0;
		for (size_t i = 1; i < n; ++i)
		{
			if (y[SA[i - 1]] == y[SA[i]] && y[SA[i - 1] + k] == y[SA[i] + k]) x[SA[i]] = p - 1;
			else x[SA[i]] = p++;
		}
		if (p >= n) break; // 每个后缀的名次已经完全不同，不需要继续倍增
		m = p; // 更新名次的最大值
	}

	// 计算 Rank 数组，用 x 存储
	for (size_t i = 0; i < n; ++i) x[SA[i]] = i;
	// 计算 Height 数组，用 y 存储
	m = 0;
	for (size_t i = 0; i < n; ++i)
	{
		if (x[i] == 0) { y[0] = 0; continue; } // 第一个后缀的最长公共前缀为 0
		if (m > 0) --m; // 从 m - 1 开始推
		size_t j = SA[x[i] - 1];
		while ((j + m < n) && (i + m < n) && (ws[j + m] == ws[i + m]))
			++m;
		y[x[i]] = m;
	}

	// 输出
	wprintf(L"\n\n ----- %s (%zd) ------", wsd, n);
	wprintf(L"\n%s", L"字符串　　　");
	for (size_t i = 0; i < n; ++i)
	{
		wchar_t c = wsd[i];
		if (c < 0x2E80) wprintf(L"　%2c", c);
		else wprintf(L"　%c", c);
	}
	wprintf(L"\n%s", L"后缀数组　　");
	for (size_t i = 0; i < n; ++i) wprintf(L"　%2llu", SA[i]);
	wprintf(L"\n%s", L"名次数组　　");
	for (size_t i = 0; i < n; ++i) wprintf(L"　%2llu", x[i]);
	wprintf(L"\n%s", L"最长公共前缀");
	for (size_t i = 0; i < n; ++i) wprintf(L"　%2llu", y[i]);

	// 清理
	delete[] wsd;
	delete[] bucket;
	delete[] x; delete[] y;
}

int main()
{
	setlocale(LC_ALL, "zh-CN");
	wchar_t const* ws1 = L"Apricot";
	wchar_t const* ws2 = L"Clang++ and LLVM";
	wchar_t const* ws3 = L"漠漠水田飞白鹭";
	pd(ws1, std::wcslen(ws1));
	pd(ws2, std::wcslen(ws2));
	pd(ws3, std::wcslen(ws3));
	wprintf(L"\n");
	return 0;
}
