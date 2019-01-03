#include "../src/utility.hpp"


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
	// ɾβ���ո�
	if (str.empty()) return;
	while (str.back() == ' ') str.pop_back();
	if (str.empty()) return;

	// ɾ�м�ո�
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

	// �ֲ���ת
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

	// ���巭ת
	reverseRegion(str, 0u, len);

	// ɾβ���ո�
	while (str.back() == ' ') str.pop_back();
}



int main()
{
	string str(" the  sky is       blue ");
	reverseWords(str);
	printf("%1s = %s/////\n", "reverseWords", str.c_str());
}
