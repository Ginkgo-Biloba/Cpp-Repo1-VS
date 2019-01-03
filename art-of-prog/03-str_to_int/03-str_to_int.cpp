#include <cctype>
#include <cstdio>
#include <climits>

/**< 字符串到整数 */
// http://taop.marchtea.com/01.03.html

int strToInt(char const* ps)
{
	int n = 0;
	static int const maxDIv10 = INT_MAX / 10;
	static int const maxMod10 = INT_MAX % 10;
	static int const minDiv10 = INT_MIN / 10 + 1;
	static int const minMod10 = INT_MIN % -10; // C++ 余数与除数同号
	// 判断是否为空
	if (ps == nullptr)return 0;
	// 跳过空格
	while (std::isspace(*ps)) ps++;
	// 检测正负
	int posNag = 1;
	while ((*ps == '+') || (*ps == '-'))
	{
		if (*ps == '-') posNag = -posNag;
		++ps;
	}
	// 确认数字
	while (std::isdigit(*ps))
	{
		// 溢出检测
		int c = *ps - '0';
		if ((posNag) > 0 && ((n > maxDIv10) || (n == maxDIv10 && c > maxMod10)))
		{
			n = INT_MAX;
			break;
		}
		else if ((posNag < 0) && ((n < minDiv10) || (n == minDiv10 && c < minMod10)))
		{
			n = INT_MIN;
			break;
		}
		// 累计结果
		n *= 10; n += c;
		++ps;
	}
	return (posNag > 0) ? n : -n;
}

int main()
{
	char const* str = "-++--234521";
	int n = strToInt(str);
	printf("%s -> %d\n", str, n);
	return 0;
}
