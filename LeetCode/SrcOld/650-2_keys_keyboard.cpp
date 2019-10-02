#include "leetcode.hpp"

/* 650. 只有两个键的键盘

最初在一个记事本上只有一个字符 'A'。你每次可以对这个记事本进行两种操作：

	Copy All (复制全部) : 你可以复制这个记事本中的所有字符(部分的复制是不允许的)。
	Paste (粘贴) : 你可以粘贴你上一次复制的字符。

给定一个数字 n 。你需要使用最少的操作次数，在记事本中打印出恰好 n 个 'A'。输出能够打印出 n 个 'A' 的最少操作次数。

示例 1:
输入: 3
输出: 3
解释:
最初, 我们只有一个字符 'A'。
第 1 步, 我们使用 Copy All 操作。
第 2 步, 我们使用 Paste 操作来获得 'AA'。
第 3 步, 我们使用 Paste 操作来获得 'AAA'。

说明:
	n 的取值范围是 [1, 1000] 。
*/

// https://leetcode.com/problems/2-keys-keyboard/discuss/105897/Loop-best-case-log(n)-no-DP-no-extra-space-no-recursion-with-explanation
// 因子分解
int minSteps(int n)
{
	int t = 0, d = 2;
	for (; d <= n; ++d)
	{
		while (n % d == 0)
		{
			n /= d;
			t += d;
		}
	}
	return t;
}


int main()
{
	OutExpr(minSteps(1), "%d");
	OutExpr(minSteps(2), "%d");
	OutExpr(minSteps(3), "%d");
	OutExpr(minSteps(4), "%d");
	OutExpr(minSteps(5), "%d");
	OutExpr(minSteps(6), "%d");
	OutExpr(minSteps(7), "%d");
	OutExpr(minSteps(8), "%d");
	OutExpr(minSteps(20), "%d");
}
