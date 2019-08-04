#include "leetcode.hpp"


int numDecodings(string const& str)
{
	int const len = static_cast<int>(str.length());
	if (len == 0) return 0;
	int* dp = static_cast<int*>(malloc((len + 1) * sizeof(int)));
	memset(dp + 1, 0x00, len * sizeof(int));
	dp[0] = 1;
	dp[1] = (str[0] != '0') ? 1 : 0;

	for (int i = 1; i < len; ++i)
	{
		int cur = str[i] - '0';
		int prev = (str[i - 1] - '0') * 10 + cur;
		if ((1 <= cur) && (cur <= 9))
			dp[i + 1] += dp[i];
		if ((10 <= prev) && (prev <= 26))
			dp[i + 1] += dp[i - 1];
	}

	int ans = dp[len];
	free(dp);
	return ans;
}

int main()
{
	int ans = numDecodings(string("226"));
	printf("%1s = %d\n", "numDecodings", ans);
}
