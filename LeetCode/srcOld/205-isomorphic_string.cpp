#include "../srcOld/utility.hpp"

/* isomorphic 同构 */
bool isIsomorphic(string const& src, string const& dst)
{
	char sd[256] = { 0 };
	char ds[256] = { 0 };
	size_t const len = src.size();

	for (size_t i = 0; i < len; ++i)
	{
		char s = src[i], d = dst[i];
		if (sd[s] != 0 && sd[s] != d)
			return false;
		else if (ds[d] != 0 && ds[d] != s)
			return false;
		else
		{
			sd[s] = d;
			ds[d] = s;
		}
	}
	return true;
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	string src("add"), dst("egg");
	bool ans = isIsomorphic(src, dst);
	printf("%1s: %s\n", "countPrimes", ans ? "T" : "F");
}
