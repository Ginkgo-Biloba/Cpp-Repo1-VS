#include "leetcode.hpp"

/* 1447. 最简分数

给你一个整数 n ，请你返回所有 0 到 1 之间（不包括 0 和 1）满足分母小于等于 n 的 最简 分数 。
分数可以以 任意 顺序返回。

示例 1：
输入：n = 2
输出：["1/2"]
解释："1/2" 是唯一一个分母小于等于 2 的最简分数。

示例 2：
输入：n = 3
输出：["1/2","1/3","2/3"]

示例 3：
输入：n = 4
输出：["1/2","1/3","1/4","2/3","3/4"]
解释："2/4" 不是最简分数，因为它可以化简为 "1/2" 。

示例 4：
输入：n = 1
输出：[]

提示：
	1 <= n <= 100
*/

int gcd(int a, int b)
{
	for (int t; b;)
	{
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

vector<string> simplifiedFractions(int n)
{
	vector<string> ans;
	char buf[32];
	for (int a = 2; a <= n; ++a)
		for (int b = 1; b < a; ++b)
		{
			int c = gcd(a, b);
			if (c == 1)
			{
				sprintf(buf, "%d/%d", b, a);
				ans.push_back(string(buf));
			}
		}
	return ans;
}


int main()
{
	output(simplifiedFractions(10), ", ");
}
