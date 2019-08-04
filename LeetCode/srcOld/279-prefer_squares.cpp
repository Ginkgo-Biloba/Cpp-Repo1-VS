#include "leetcode.hpp"


// 一般用动态规划，加上 vector 或 map 或 unordered_map 当缓存
// 这里抄的四平方和定理 (Lagrange's four-square theorem)
// 所以答案只可能是 1 2 3 4

bool isSquare(int n)
{
	int r = static_cast<int>(sqrt(static_cast<double>(n)));
	return r * r == n;
}


int numSquares(int n)
{
	if (isSquare(n))
		return 1;

	// 结果是 4，当且仅当 n 可以写作 (4^k * (8*m+7))
	while ((n & 3) == 0) // n 是 4 的倍数
		n >>= 2;
	if ((n & 7) == 7) // n % 8 == 7
		return 4;

	// 检查 2 个平方数行不行
	int r = static_cast<int>(sqrt(static_cast<double>(n)));
	for (int i = 1; i <= r; ++i)
	{
		if (isSquare(n - i * i))
			return 2;
	}

	// 否则就是 3
	return 3;
}


int main()
{
	int n = numSquares(60);
	printf("numSquares: %d\n", n);
}
