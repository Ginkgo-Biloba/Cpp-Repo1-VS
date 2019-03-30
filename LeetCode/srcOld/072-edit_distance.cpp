#include "../srcOld/utility.hpp"

int minDistance(string const& src, string const& dst)
{
	size_t const slen = src.length(), dlen = dst.length();
	vector<size_t> curr(dlen + 1u), prev(dlen + 1u);
	for (size_t d = 0; d <= dlen; ++d)
		curr[d] = d;

	for (size_t s = 0; s < slen; ++s)
	{
		char const ch = src[s];
		prev.swap(curr);
		curr[0] = s + 1u;
		for (size_t d = 0u; d < dlen; ++d)
		{
			size_t cd = std::min(prev[d + 1u], curr[d]) + 1u;
			if (ch == dst[d])
				cd = std::min(cd, prev[d]);
			else
				cd = std::min(cd, prev[d] + 1u);
			curr[d + 1u] = cd;
		}
	}

	int const ans = static_cast<int>(curr.back());
	return ans;
}


int main()
{
	int ans = minDistance(string("horse"), string("ros"));
	printf("%1s = %d\n", "minDistance", ans);
}
