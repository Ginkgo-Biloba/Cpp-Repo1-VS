#include "../srcOld/utility.hpp"

int nextNum(string const& str, int& idx)
{
	int const len = static_cast<int>(str.size());
	if (idx >= len) return 0;
	int ans = 0;
	for (; idx < len; ++idx)
	{
		if (str[idx] == '.') break;
		ans = ans * 10 + str[idx] - '0';
	}
	return ans;
}

int compareVersion(string const& X, string const& Y)
{
	int const len = static_cast<int>(std::max(X.size(), Y.size()));

	int ix = 0, iy = 0;
	while (ix < len && iy < len)
	{
		int nx = nextNum(X, ix);
		int ny = nextNum(Y, iy);
		if (nx > ny) return 1;
		if (nx < ny) return -1;
		++ix; ++iy;
	}
	return 0;
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	vector<int> nums = { 1, 2, 1, 3, 5, 6, 4 };
	int ans = compareVersion(string("1"), string("1.0"));
	printf("%1s = %d \n", "compareVersion", ans);
}
