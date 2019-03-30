#include "../srcOld/utility.hpp"

/* Given a string S and a string T,
 * count the number of distinct subsequences of S which equals T. */

int numDistinct0(string const& S, string const& T)
{
	size_t lenS = S.size(), lenT = T.size();
	if (lenS < lenT) return 0;
	int* dp = static_cast<int*>(malloc((lenT + 1u) * sizeof(int)));
	dp[0] = 1;
	memset(dp + 1, 0x00, lenT * sizeof(int));

	for (size_t ls = 1; ls <= lenS; ++ls)
	{
		char const curS = S[ls - 1u];
		int oldprev = 1, oldcur;
		for (size_t lt = 1; lt <= lenT; ++lt)
		{
			oldcur = dp[lt];
			if (curS == T[lt - 1u])
				dp[lt] += oldprev;
			oldprev = oldcur;
		}
	}

	int ans = dp[lenT];
	free(dp);
	return ans;
}

int numDistinct(string const& src, string const& dst)
{
	int const slen = static_cast<int>(src.size());
	int const dlen = static_cast<int>(dst.size());
	// 空字符串不包含任何非空字符串
	// leetcode 竟然改数据范围了，之前 int 是可以的
	vector<unsigned> prev(dlen + 1), cur(dlen + 1, 0);
	cur[0] = 1; // 任意字符串都包含一个空字符串

	for (int s = 0; s < slen; ++s)
	{
		prev.swap(cur);
		cur[0] = 1;
		for (int d = 0; d < dlen; ++d)
		{
			if (src[s] == dst[d])
				cur[d + 1] = prev[d] + prev[d + 1];
			else
				cur[d + 1] = prev[d + 1];
		}
	}

	return static_cast<int>(cur.back());
}


int main()
{
	string src = "rabbbit", dst = "rabbit";
	printf("%d\n", numDistinct(src, dst));
}
