#include "leetcode.hpp"

/* 1012. 至少有 1 位重复的数字

给定正整数 N，返回小于等于 N 且具有至少 1 位重复数字的正整数。

示例 1：
输入：20
输出：1
解释：具有至少 1 位重复数字的正数（<= 20）只有 11 。

示例 2：
输入：100
输出：10
解释：具有至少 1 位重复数字的正数（<= 100）有 11，22，33，44，55，66，77，88，99 和 100 。

示例 3：
输入：1000
输出：262

提示：
	1 <= N <= 10^9
*/

int A(int m, int n)
{
	return n == 0 ? 1 : (A(m, n - 1) * (m - n + 1));
}

// https://leetcode.com/problems/numbers-with-repeated-digits/discuss/256725/JavaPython-Count-the-Number-Without-Repeated-Digit
// 抄的
int numDupDigitsAtMostN(int N)
{
	// Transform N + 1 to arrayList
	vector<int> L;
	for (int x = N + 1; x > 0; x /= 10)
		L.push_back(x % 10);
	reverse(L.begin(), L.end());

	// Count the number with digits < N
	int ans = 0, n = static_cast<int>(L.size());
	for (int i = 1; i < n; ++i)
		ans += 9 * A(9, i - 1);

	unordered_set<int> seen;
	for (int i = 0; i < n; ++i)
	{
		// 开头不能是 0
		int k = (i == 0);
		for (; k < L[i]; ++k)
		{
			if (seen.find(k) == seen.end())
				ans += A(9 - i, n - i - 1);
		}
		if (!(seen.insert(L[i]).second))
			break;
	}

	return N - ans;
}


int main()
{
	OutExpr(numDupDigitsAtMostN(20), "%d");
	OutExpr(numDupDigitsAtMostN(100), "%d");
	OutExpr(numDupDigitsAtMostN(1000), "%d");
}
