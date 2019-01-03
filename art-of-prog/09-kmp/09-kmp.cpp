#include <clocale>
#include <cwchar>
#include <cstring>
#include <cstdio>

/**< KMP 算法 */
// Knuth-Morris-Pratt 字符串查找算法
// Ref: http://www.cnblogs.com/yjiyjige/p/3263858.html
// Ref: http://blog.csdn.net/v_july_v/article/details/7041827

// Next 数组，保证已分配内存
void calcNext(wchar_t const* ws, int const& n, int* Next)
{
	int const n1 = n - 1;
	Next[0] = -1;
	int iL = -1;
	int iR = 0; // 0 和 1 是为了不和不存在的 ws[-1] 比较
	while (iR < n1)
	{
		if (iL == -1 || ws[iL] == ws[iR])
		{
			++iL; ++iR; // 多一个相同的字符
			Next[iR] = iL;
		}
		else
			iL = Next[iL];
	}
}

// 查找，返回 wsA 中匹配 wsB 的开头位置，只查找第一次出现的地方
int wstrSearch(wchar_t const* wsA, int const& lenA, wchar_t const* wsB, int const& lenB)
{
	if (lenB <= 0 || lenA < lenB) return -1;
	int* NextB = new int[lenB];
	calcNext(wsB, lenB, NextB);
	for (int i = 0; i < lenB; ++i)
		printf("%d  ", NextB[i]);
	int iA = 0; // 查找字符串位置
	int iB = 0; // 模式字符串位置
	while (iA < lenA && iB < lenB)
	{
		if (iB == -1 || wsA[iA] == wsB[iB])
		{ ++iA; ++iB; } // 有字符串相同，都前移
		else
			iB = NextB[iB]; // 只用回溯 iB
	}
	if (iB == lenB) return (iA - iB);
	else return -1;
}

int main()
{
	setlocale(LC_ALL, "zh-CN");
	wchar_t const A[] = L"吃葡萄不吐葡萄皮，不吃葡萄倒吐葡萄皮。";
	wchar_t const B[] = L"葡萄不吐葡萄皮";
	int pos = wstrSearch(A, (int)(wcslen(A)), B, (int)(wcslen(B)));
	wprintf(L"\nPosition: %d", pos);
	wprintf(L"\n\n");
}
