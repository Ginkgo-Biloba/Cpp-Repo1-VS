#include "../src/utility.hpp"


// dp[i] 存储的是 str[0:i) 能解码的方式数量
int numDecodings(string const& str)
{
	int64_t const modNum = 1000000007;
	int const len = static_cast<int>(str.length());
	if ((len == 0) || (str[0] == '0')) return 0;

	int64_t* dp = static_cast<int64_t*>(malloc((len + 1) * sizeof(int64_t)));
	memset(dp + 1, 0x00, len * sizeof(int64_t));
	dp[0] = 1;
	dp[1] = (str[0] == '*') ? 9 : 1;

	for (int i = 1; i < len; ++i)
	{
		char prev = str[i - 1];
		char cur = str[i];

		// dp[i] 仅仅不包含当前字符
		if (cur == '*')
			dp[i + 1] += 9 * dp[i];
		else if (cur > '0')
			dp[i + 1] += dp[i];

		// dp[i - 1] 不包含当前字符和前一个字符
		if (prev == '*')
		{
			if (cur == '*')
				dp[i + 1] += 15 * dp[i - 1]; // [11, 26] - 20
			else if (cur <= '6')
				dp[i + 1] += 2 * dp[i - 1]; // 1*, 2*
			else
				dp[i + 1] += dp[i - 2]; // 1*
		}
		else if((prev == '1') || (prev == '2'))
		{
			if (cur == '*')
			{
				if (prev == '1')
					dp[i + 1] += 9 * dp[i - 1]; // 1*
				else
					dp[i + 1] += 6 * dp[i - 1]; // 2*
			}
			else if (((prev - '0') * 10 + (cur - '0')) <= 26)
				dp[i + 1] += dp[i - 1];
		}
		dp[i + 1] %= modNum;
	}

	int ans = static_cast<int>(dp[len]);
	free(dp);
	return ans;
}

int main()
{
	int ans = numDecodings(string("**********1111111111"));
	printf("%1s = %d\n", "numDecodings", ans); // 133236775
}
