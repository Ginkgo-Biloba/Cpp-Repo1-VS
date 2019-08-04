#include "leetcode.hpp"


void reverseRegion(string& str, unsigned l, unsigned r)
{
	if (l >= r) return;

	for (--r; l < r; ++l, --r)
	{
		char c = str[l];
		str[l] = str[r]; str[r] = c;
	}
}


void reverseWords(string &str)
{
	// 删尾部空格
	if (str.empty()) return;
	while (str.back() == ' ') str.pop_back();
	if (str.empty()) return;

	// 删中间空格
	unsigned len = static_cast<unsigned>(str.size());
	unsigned prev = 0u, cur = 0u;
	while ((cur < len) && (str[cur] == ' ')) ++cur;
	while (cur < len)
	{
		if (str[cur] == ' ')
		{
			str[prev] = str[cur];
			++prev; ++cur;
			while ((cur < len) && (str[cur] == ' ')) ++cur;
		}
		str[prev] = str[cur];
		++prev; ++cur;
	}
	for (; cur != prev; --cur)
		str.pop_back();

	// 局部翻转
	len = prev;
	prev = cur = 0u;
	for (; cur < len; ++cur)
	{
		if (str[cur] == ' ')
		{
			reverseRegion(str, prev, cur);
			prev = cur + 1u;
		}
	}
	reverseRegion(str, prev, len);

	// 整体翻转
	reverseRegion(str, 0u, len);

	// 删尾部空格
	while (str.back() == ' ') str.pop_back();
}



int main()
{
	string str(" the  sky is       blue ");
	reverseWords(str);
	printf("%1s = %s/////\n", "reverseWords", str.c_str());
}
