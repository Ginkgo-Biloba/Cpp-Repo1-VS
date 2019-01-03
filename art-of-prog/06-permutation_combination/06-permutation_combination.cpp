#include <cwchar>
#include <locale>
#include <cstring>
#include <cstdio>

/**< 全排列与全组合 */

// 字典序全排列，当总数超过 size_t 范围时返回值不正确，当依然全部输出
// http://taop.marchtea.com/01.06.html
size_t dictPerm(wchar_t const* ws, size_t const n)
{
	if (ws == nullptr || n == 0)
		return 0;
	// 先排序，复制一个，选择排序即可
	wchar_t* const wsd = new wchar_t[n + 1]; // 指针 wsd 不能动
	size_t const n1 = n - 1;
	std::memcpy(wsd, ws, n * sizeof(wchar_t));
	wsd[n] = L'\0';
	for (size_t i = 0; i < n1; ++i)
	{
		wchar_t c = wsd[i];
		size_t cx = i;
		for (size_t k = i + 1; k < n; ++k)
			if (c > wsd[k])
			{ c = wsd[k]; cx = k; }
		wsd[cx] = wsd[i]; wsd[i] = c;
	}
	bool isDictMax = false; // 是否是最大字典序

	size_t N = 0; // 计数
	while (!isDictMax)
	{
		++N;
		// 输出当前（刚排好序的最小字典序，或者上一次循环的结果）
		wprintf(L"\n%s", wsd);
		size_t k, m; // 向前寻找，如果 k 为前一个字符的索引则不能用 size_t 类型
		// 找到第一个相邻的、前一个比后一个小的位置
		for (k = n1; k > 0; --k)
			if (wsd[k - 1] < wsd[k])
				break;
		// 如果没找到，说明当前为最大字典序
		if (k == 0) isDictMax = true;
		else
		{
			wchar_t const ck1 = wsd[k - 1];
			// 找到 (k - 1) 右边、从右向左数第一个比 wsd[k - 1] 大的数
			for (m = n1; m >= k; --m)
				if (wsd[k - 1] < wsd[m])
					break;
			// 交换位置
			wsd[k - 1] = wsd[m];
			wsd[m] = ck1;
			// 翻转字符串 [k, n] 部分
			for (m = n1; k < m; ++k, --m)
			{
				wchar_t const ck = wsd[k];
				wsd[k] = wsd[m];
				wsd[m] = ck;
			}
		}
	}
	delete[] wsd;
	return N;
}

// 全组合，位操作，受限于 size_t 的位数，且不能处理重复字符的情况
size_t bitArrange(wchar_t const* ws, size_t const n)
{
	if (ws == nullptr || n == 0) return 0;
	size_t totalNum = (1 << n);
	for (size_t i = 1; i < totalNum; ++i)
	{
		wprintf(L"\n");
		for (size_t k = 0; k < n; ++k)
			if (i & ((size_t)(1) << k)) // 如果对应为上是 1，则输出对应字符
				wprintf(L"%c", ws[k]);
	}
	return totalNum;
}

int main()
{
	setlocale(LC_ALL, "zh-CN");
	wchar_t const* ws1 = L"LLVM";
	wchar_t const* ws2 = L"落叶纷纷";
	//	wprintf(L"%d", sizeof(wchar_t));

#define PERMUTATION(ws, func) \
	wprintf(L"\n\n----- 字符串 %s (%zd) 的全排列是 -----", ws, wcslen(ws)); \
	func(ws, wcslen(ws));
#define ARRANGE(ws, func) \
	wprintf(L"\n\n----- 字符串 %s (%zd) 的全组合是 -----", ws, wcslen(ws)); \
	func(ws, wcslen(ws));

	PERMUTATION(ws1, dictPerm);
	PERMUTATION(ws2, dictPerm);
	ARRANGE(ws1, bitArrange);
	ARRANGE(ws2, bitArrange);
#undef PERMUTATION
#undef ARRANGE
	wprintf(L"\n");
	return 0;
}
