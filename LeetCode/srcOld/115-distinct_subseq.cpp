#include "../src/utility.hpp"

int numDistinct(string const& S, string const& T)
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

int main()
{
	int ans = numDistinct(string("rabbbit"), string("rabbit"));
	printf("%1s = %d\n", "numDistinct", ans);
}
