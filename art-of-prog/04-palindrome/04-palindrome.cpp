#include <cwchar>
#include <locale>
#include <cstdio>

/**< 判断回文字符串 */
// Ref: http://taop.marchtea.com/01.04.html

// 从开头和结尾两端同时向中间扫描
bool isPdr1(wchar_t const* ws, size_t n)
{
	if (ws == nullptr || n < 1u) return false;
	size_t left = 0;
	size_t right = n - 1;
	while (left < right)
	{
		if (ws[left] != ws[right]) return false;
		++left; --right;
	}
	return true;
}

// 从中间开始向两头扫描，1-5 中也使用了
bool isPdr2(wchar_t const* ws, size_t n)
{
	if (ws == nullptr || n == 0) return false;
	size_t n1 = n - 1;
	size_t mid1 = (n1 >> 1);
	size_t mid2 = n1 - mid1;
	while (mid2 < n1)
	{
		if (ws[mid1] != ws[mid2]) return false;
		--mid1; ++mid2;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "zh-CN");
	// Able was I ere I saw elba. 在我看到厄尔巴岛之前，我曾所向无敌。
	wchar_t const* ws1 = L"able was I ere I saw elba";
	wchar_t const* ws2 = L"上海自来水来自海上";
	wchar_t const* ws3 = L"矮纸斜行闲作草";
#define TEST_PDR(x, pre) \
	wprintf(L"\n%s -> %s\n", x, (pre(x, std::wcslen(x))? L"是" : L"否"))
	TEST_PDR(ws1, isPdr1);
	TEST_PDR(ws2, isPdr2);
	TEST_PDR(ws3, isPdr2);
#undef TEST_PDR
	return 0;
}
