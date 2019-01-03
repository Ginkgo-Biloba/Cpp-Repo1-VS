#include "../src/utility.hpp"

bool isLongPressedName(string const& name, string const& typed)
{
	unsigned const nlen = (unsigned)(name.length());
	unsigned const tlen = (unsigned)(typed.length());
	if (tlen < nlen)
		return false;

	unsigned n = 0u, t = 0u;
	char prev = '\0';
	while ((n < nlen) && (t < tlen))
	{
		if (name[n] == typed[t])
		{
			prev = name[n];
			++t; ++n;
		}
		else if (prev == typed[t])
			++t;
		else // 出循环
			t = tlen;
	}
	while ((t < tlen) && (prev == typed[t]))
		++t;

	return (n == nlen) && (t == tlen);
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	vector<int> nums = { 3, 3, 1, 3 };
	string name("vtkgn"), typed("vtkgnn");
	int ans = isLongPressedName(name, typed);
	printf("%1s = %s\n", "isLongPressedName", \
		(ans ? "true" : "false"));
}
