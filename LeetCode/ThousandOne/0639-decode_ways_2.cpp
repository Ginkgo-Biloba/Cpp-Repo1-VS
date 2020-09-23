#include "leetcode.hpp"

/* 639. 解码方法 2

一条包含字母 A-Z 的消息通过以下的方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26

除了上述的条件以外，现在加密字符串可以包含字符 '*'了，字符'*'可以被当做1到9当中的任意一个数字。

给定一条包含数字和字符'*'的加密信息，请确定解码方法的总数。

同时，由于结果值可能会相当的大，所以你应当对10^9 + 7取模。（翻译者标注：此处取模主要是为了防止溢出）

示例 1 :
输入: "*"
输出: 9
解释: 加密的信息可以被解密为: "A", "B", "C", "D", "E", "F", "G", "H", "I".

示例 2 :
输入: "1*"
输出: 9 + 9 = 18（翻译者标注：这里1*可以分解为1,* 或者当做1*来处理，所以结果是9+9=18）

说明 :
输入的字符串长度范围是 [1, 105]。
输入的字符串只会包含字符 '*' 和 数字'0' - '9'。
*/

int numDecodings(string const& str)
{
	int64_t const modNum = 1000000007;
	int const len = static_cast<int>(str.length());
	if ((len == 0) || (str[0] == '0'))
		return 0;

	// dp[i] 存储的是 str[0:i) 能解码的方式数量
	vector<int64_t> dp(len + 1);
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
		else if ((prev == '1') || (prev == '2'))
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

	return dp.back();
}


int main()
{
	OutExpr(
		numDecodings(string("**********1111111111")),
		"%d"); // 133236775
}
