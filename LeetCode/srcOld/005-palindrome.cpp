#include <cwchar>
#include <locale>
#include <cstdio>
#include <cstring>

/* 005 最长回文子串 */

// 取一字符作为中间，向两边扫描。复杂度 O(N^2)
// Ref: http://taop.marchtea.com/01.05.html
size_t lpdr1(wchar_t const* ws, size_t const n)
{
	if (ws == nullptr || n == 0) return 0;
	size_t rst = 0;
	size_t const n1 = n - 1;
	for (size_t i = 1; i < n1; ++i) // 第一个和最后一个显然不能作为中心
	{
		size_t len = 1;
		for (size_t k = 1; (k <= i) && (i + k) < n; ++k) // 假设长度是奇数
		{
			if (ws[i - k] == ws[i + k]) len += 2;
			else break;
		}
		if (rst < len) rst = len;
		len = 0;
		for (size_t k = 0; (k <= i) && (i + k + 1) < n; ++k) // 假设长度是偶数
		{
			if (ws[i - k] == ws[i + k + 1]) len += 2;
			else break;
		}
		if (rst < len) rst = len;
	}
	return rst;
}

// Manacher 算法。复杂度 O(N)
/* Ref: https://segmentfault.com/a/1190000003914228
(1) 解决长度奇偶性带来的对称轴位置问题
Manacher算法首先对字符串做一个预处理，在所有的空隙位置(包括首尾)插入同样的符号，要求这个符号是不会在原串中出现的。
这样会使得所有的串都是奇数长度的。以插入#号为例：
aba  ———>  #a#b#a#
abba ———>  #a#b#b#a#
为了进一步减少编码的复杂度，可以在字符串的开始加入另一个特殊字符，这样就不用特殊处理越界问题，比如 $#a#b#a#。
(2) 解决重复访问的问题
我们把一个回文串中最左或最右位置的字符与其对称轴的距离称为回文半径。
Manacher定义了一个回文半径数组RL，用RL[i]表示以第i个字符为对称轴的回文串的回文半径。
我们一般对字符串从左往右处理，因此这里定义RL[i]为第i个字符为对称轴的回文串的最右一个字符与字符i的距离。
对于上面插入分隔符之后的两个串，可以得到RL数组：
char:    # a # b # a #
RL  :    1 2 1 4 1 2 1
RL-1:    0 1 0 3 0 1 0
i   :    0 1 2 3 4 5 6
char:    # a # b # b # a #
RL  :    1 2 1 2 5 2 1 2 1
RL-1:    0 1 0 1 4 1 0 1 0
i    :    0 1 2 3 4 5 6 7 8
上面我们还求了一下 RL[i] - 1。
通过观察可以发现，RL[i] - 1的值，正是在原本那个没有插入过分隔符的串中，以位置i为对称轴的最长回文串的长度。
那么只要我们求出了RL数组，就能得到最长回文子串的长度。
于是问题变成了，怎样高效地求的RL数组。基本思路是利用回文串的对称性，扩展回文串。*/
size_t manacher(wchar_t const* ws, size_t const n)
{
	if (ws == nullptr || n == 0) return 0;
	// 假设字符串中不包含这俩字符，它们需要在 Windows.936 编码中
	wchar_t const wc1 = L'■'; // 实心方形 U+25A0
	wchar_t const wc2 = L'●'; // 实心圆圈 U+25CF
	size_t const xn = (n << 1) + 3; // 开头，两边，结尾
	size_t const xn1 = xn - 1;
	// 生成新字符串，指针 wsEx 不能动
	wchar_t* const wsEx = new wchar_t[xn];
	for (int i = 0; i < n; ++i)
	{
		wsEx[(i << 1) + 1] = wc2;
		wsEx[(i << 1) + 2] = ws[i];
	}
	wsEx[0] = wc1; // 开头
	wsEx[xn - 2] = wc2; wsEx[xn1] = L'\0'; // 结尾
	wprintf(L"\n新字符串 (%zd)：%s", xn, wsEx);
	size_t maxR = 1; size_t pos = 1; // 第一个字符显然不行
	size_t* const rl = new size_t[xn]; // 记录回文半径，指针 rl 不能动
	std::memset(rl, 0, xn * sizeof(size_t));
	rl[1] = 1;
	for (int i = 1; i < xn1; ++i)
	{
		size_t rl1 = rl[2 * pos - i];
		size_t rl2 = (pos > i) ? (pos - i) : 1;
		size_t rlx = (rl1 < rl2) ? rl1 : rl2; // 回文半径
		while (wsEx[i + rlx] == wsEx[i - rlx])
			++rlx;
		// 无需处理边界，因为假设开头字符不存在原字符串中，结尾 '\0' 当然也不会存在
		rl[i] = rlx;
		if (maxR < i + rlx)
		{ maxR = i + rlx; pos = i; }
	}
	// 找到 rl 中最大的，第一个和最后一个肯定不是
	size_t rst = 1;
	for (int i = 2; i < xn1; ++i)
		if (rst < rl[i])
			rst = rl[i];
	delete[] wsEx; delete[] rl;
	return (rst - 1); // 需要减 1，因为 rlx 最小值为 1，即回文半径包含轴自身
}


int main()
{
	setlocale(LC_ALL, "zh-CN");
	// Able was I ere I saw elba. 在我看到厄尔巴岛之前，我曾所向无敌。
	wchar_t const* ws1 = L"Able was I ere I saw elba";
	wchar_t const* ws2 = L"上海自来水来自海上";
	wchar_t const* ws3 = L"留连戏蝶时时舞";
	wchar_t const* ws4 = L"晴窗细乳戏分茶";
#define TEST_PDR(x, func) \
	wprintf(L"\n%s (%zd) -> %zd\n", x, std::wcslen(x), func(x, std::wcslen(x)))
	TEST_PDR(ws1, lpdr1);
	TEST_PDR(ws2, lpdr1);
	TEST_PDR(ws3, manacher);
	TEST_PDR(ws4, manacher);
#undef TEST_PDR
	return 0;
}
