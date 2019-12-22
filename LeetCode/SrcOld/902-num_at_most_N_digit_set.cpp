#include "leetcode.hpp"

/* 902. 最大为 N 的数字组合

我们有一组排序的数字 D，它是  {'1','2','3','4','5','6','7','8','9'} 的非空子集。
请注意，'0' 不包括在内。

现在，我们用这些数字进行组合写数字，想用多少次就用多少次。
例如 D = {'1','3','5'}，我们可以写出像 '13', '551', '1351315' 这样的数字。

返回可以用 D 中的数字写出的小于或等于 N 的正整数的数目。

示例 1：
输入：D = ["1","3","5","7"], N = 100
输出：20
解释：
可写出的 20 个数字是：
1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.

示例 2：
输入：D = ["1","4","9"], N = 1000000000
输出：29523
解释：
我们可以写 3 个一位数字，9 个两位数字，27 个三位数字，
81 个四位数字，243 个五位数字，729 个六位数字，
2187 个七位数字，6561 个八位数字和 19683 个九位数字。
总共，可以使用D中的数字写出 29523 个整数。

提示：
	D 是按排序顺序的数字 '1'-'9' 的子集。
	1 <= N <= 10^9
*/

// https://leetcode.com/problems/numbers-at-most-n-given-digit-set/discuss/168439/C%2B%2B-O(logN)-Clear-code-with-explanation
// 抄的
int atMostNGivenDigitSet(vector<string>& D, int n)
{
	string N = std::to_string(n);
	int digit = static_cast<int>(N.size());
	int dsize = static_cast<int>(D.size());
	int sum = 0, base = 1;

	for (int i = 1; i < digit; ++i)
	{
		base *= dsize;
		sum += base; // pow(dsize, i)
	}

	for (int i = 0; i < digit; ++i)
	{
		bool hasSame = false;
		for (string& d : D)
		{
			if (d[0] < N[i])
				sum += base; // pow(dsize, digit - 1 - i)
			else if (d[0] == N[i])
				hasSame = true;
		}
		if (!hasSame)
			return sum;
		base /= dsize;
	}

	// 可能有 N
	return sum + 1;
}


int main()
{
	vector<string>
		a = { "1", "3", "5", "7" },
		b = { "1", "4", "9" },
		c = { "5", "7", "8" };
	OutExpr(atMostNGivenDigitSet(a, 100), "%d");
	OutExpr(atMostNGivenDigitSet(b, 1000000000), "%d");
	OutExpr(atMostNGivenDigitSet(c, 59), "%d");
}
