#include <string>
#include <cstdio>
#include <cstdint>
#include <cmath>
using std::string;

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




