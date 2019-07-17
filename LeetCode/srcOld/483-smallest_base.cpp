#include <string>
#include <cstdio>
#include <cstdint>
#include <cmath>
using std::string;

/* 483. 最小好进制

对于给定的整数 n, 如果n的k（k>=2）进制数的所有数位全为1，则称 k（k>=2）是 n 的一个好进制。
以字符串的形式给出 n, 以字符串的形式返回 n 的最小好进制。

示例 1：
输入："13"
输出："3"
解释：13 的 3 进制是 111。

示例 2：
输入："4681"
输出："8"
解释：4681 的 8 进制是 11111。

示例 3：
输入："1000000000000000000"
输出："999999999999999999"
解释：1000000000000000000 的 999999999999999999 进制是 11。

提示：

n的取值范围是 [3, 10^18]。
输入总是有效且没有前导 0。
*/


string smallestGoodBase(string const& str)
{
	uint64_t val = 0;;
	for (char const c : str)
	{ val *= 10u; val += (c - '0'); }

	// k 是基，m 是位数
	uint64_t m = (uint64_t)(std::log2(val + 1u));
	uint64_t k = 1u, f, l, r;
	for (; (m >= 2) && (k); m--)
	{
		l = (uint64_t)(std::pow(val + 1u, 1.0 / m));
		r = (uint64_t)(std::pow(val, 1.0 / (m - 1)));
		while (l <= r)
		{
			k = (l + r) / 2u;
			f = 0u;
			for (int i = 0; i < m; i++)
			{ f *= k; f += 1u; }
			if (val == f)
				return std::to_string(k);
			else if (val < f)
				r = k - 1u;
			else
				l = k + 1u;
		}
	}

	return std::to_string(val - 1u);
}

int main()
{
	string str("1000000000000000000");
	string ans = smallestGoodBase(str);
	printf("ans = %s\n", ans.c_str());
	return 0;
}




