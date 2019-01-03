#include <cwchar>
#include <locale>
#include <cstring>
#include <iostream>

/**< 平移字符串 */
// Ref: http://taop.marchtea.com/01.01.html
// rev[rev(X),rev(Y)] = Y,X

void revWstr(wchar_t* ws, int from, int to)
{
	for (; from < to; ++from, --to)
	{
		wchar_t wt = ws[from];
		ws[from] = ws[to];
		ws[to] = wt;
	}
}

// 将 n 个字符的字符串循环左移 m 位
void leftRotWstr(wchar_t* ws, int n, int m)
{
	m %= n; // 左移位数大于 n，则与左移 %n 位等价
	revWstr(ws, 0, m - 1);
	revWstr(ws, m, n - 1);
	revWstr(ws, 0, n - 1);
}

int main()
{
	std::wcout.imbue(std::locale("zh-CN"));
	std::wcout << L"左移五个字符：\n";
	wchar_t wp[32] = L"A|一个|Test|测试";
	std::wcout << wp << " -> ";
	leftRotWstr(wp, static_cast<int>(wcslen(wp)), 5);
	std::wcout << wp << std::endl;
	return 0;
}
