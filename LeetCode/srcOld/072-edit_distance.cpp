#include "leetcode.hpp"

/* 72. 编辑距离

给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：
	插入一个字符
	删除一个字符
	替换一个字符

示例 1：
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

示例 2：
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
*/

int minDistance(string A, string B)
{
	if (A.length() > B.length())
		A.swap(B);
	int a = static_cast<int>(A.length());
	int b = static_cast<int>(B.length());
	vector<int> dp(b + 1), eq(b + 1);
	for (int k = 0; k <= b; ++k)
		dp[k] = k;
	for (int i = 0; i < a; ++i)
	{
		dp.swap(eq);
		dp[0] = i + 1;
		for (int k = 0; k < b; ++k)
		{
			if (A[i] == B[k])
				dp[k + 1] = eq[k];
			else
				dp[k + 1] = min(dp[k], min(eq[k], eq[k + 1])) + 1;
		}
	}
	return dp[b];
}


int main()
{
	OutExpr(minDistance("horse", "ros"), "%d");
	OutExpr(minDistance("intention", "execution"), "%d");
	OutExpr(minDistance("", ""), "%d");
}
