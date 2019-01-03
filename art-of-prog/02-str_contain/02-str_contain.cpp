#include <cwchar>
#include <locale>
#include <cstring>
#include <iostream>
using std::wcin; using std::wcout;
using std::endl;
#include <string>
using std::wstring; using std::string;
#include <algorithm>

/**< 字符串包含判断 */
// http://taop.marchtea.com/01.02.html

// 暴力查找
bool wstrCont1(wstring const& a, wstring const& b)
{
	for (size_t i = 0u; i < b.length(); ++i)
	{
		size_t j;
		for (j = 0; j < a.length(); ++j)
			if (a[j] == b[i]) break;
		if (j >= a.length()) return false;
	}
	return true;
}

// 如果允许排序，可以对字符串进行轮询扫描
bool wstrCont2(wstring& a, wstring& b)
{
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	for (size_t pa = 0, pb = 0; pb < b.length();)
	{
		while ((pa < a.length()) && (a[pa] < b[pb]))
			++pa;
		if ((pa >= a.length()) || a[pa] > b[pb])
			return false;
		++pb; // a[pa] == b[pb]
	}
	return true;
}

// 使用质数乘积，根据余数判断
// 只有理论意义，只能判断有限个字符 (26 个大写字母)
bool strCont1(string &a, string &b)
{
	const int p[26] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101 };
	int f = 1;
	for (int i = 0; i < a.length(); ++i)
	{
		int x = p[a[i] - 'A'];
		if (f % x) f *= x;
	}
	for (int i = 0; i < b.length(); ++i)
	{
		int x = p[b[i] - 'A'];
		if (f % x) return false;
	}
	return true;
}

// 用异或运算当散列函数，用字符对应编码的整数表示签名
// 也只能测试有限个字符 (26 个大写字母，sizeof(unsigned int) = 32)
bool strCont2(string const& a, string const& b)
{
	unsigned int hash = 0u;
	for (int i = 0; i < a.length(); ++i)
		hash |= (1 << (a[i] - 'A'));
	for (int i = 0; i < b.length(); ++i)
		if ((hash & (1 << (b[i] - 'A'))) == 0)
			return false;
	return true;
}

int main()
{
	wcout.imbue(std::locale("zh-CN"));
	wstring ws1(L"Test 你好 Hello");
	wstring ws2(L"Hello 好");
	wstring ws3(L"Test 你那");
	wcout << ws1 << L" ->>- " << ws2 << L" => "
		<< std::boolalpha << wstrCont1(ws1, ws2) << endl;
	wcout << ws1 << L" ->>- " << ws3 << L" => " << std::flush
		<< std::boolalpha << wstrCont2(ws1, ws3) << endl;
	return 0;
}
