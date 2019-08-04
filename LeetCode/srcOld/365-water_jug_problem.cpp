#include "leetcode.hpp"

/* 365. 水壶问题

有两个容量分别为 x升 和 y升 的水壶以及无限多的水。
请判断能否通过使用这两个水壶，从而可以得到恰好 z升 的水？

如果可以，最后请用以上水壶中的一或两个来盛放取得的 z升 水。

你允许：
- 装满任意一个水壶
- 清空任意一个水壶
- 从一个水壶向另外一个水壶倒水，直到装满或者倒空

示例 1: (From the famous "Die Hard" example)
输入: x = 3, y = 5, z = 4
输出: True

示例 2:
输入: x = 2, y = 6, z = 5
输出: False
*/

// https://leetcode.com/problems/water-and-jug-problem/discuss/83715/Math-solution-Java-solution
// 抄的
bool canMeasureWater(int x, int y, int z)
{
	if (x + y < z)
		return false;
	if (x == z || y == z || x + y == z)
		return true;

	// 最大公约数
	while (x)
	{
		int t = y % x;
		y = x;
		x = t;
	}

	return z % y == 0;
}

// https://leetcode.com/problems/water-and-jug-problem/discuss/83727/c%2B%2B-solution-follow-the-procedure
bool canMeasure(int x, int y, int z)
{
	if (x + y = z)
		return true;
	if (x + y < z)
		return false;
	if (x > y)
		std::swap(x, y);

	int cur = 0;
	for (;;)
	{
		if (cur < x)
			cur += y;
		else
			cur -= x;
		if (cur == z)
			return true;
		if (cur == 0)
			return false;
	}
}


int main()
{
	bool ans = canMeasureWater(3, 5, 4);
	printf("maxSumSubmatrix: %s\n", boolstr[ans]);
}
