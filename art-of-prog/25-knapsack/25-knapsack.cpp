#include <cstdio>
#include <cstring>

/**< 背包问题 */
// Ref: http://www.hawstein.com/posts/dp-knapsack.html

int main()
{
	int const n = 5; // 物品个数
	int const C = 10; // 背包容量
	int const diam[n][2] = { { 2, 6 }, { 2, 3 }, { 6, 5 }, { 5, 4 }, { 4, 6 } }; // 1, 1, 0, 0, 1; 15
	int sln[n]; // 存放答案
	int d[n + 1][C + 1]; // 状态变量
	memset(d, 0, (C + 1) * sizeof(int)); // 第一行置 0
	int k, m;
	// 循环
	for (k = 0; k < n; ++k)
	{
		d[k + 1][0] = 0; // 第一列置 0
		for (m = 1; m <= C; ++m)
		{
			d[k + 1][m] = d[k][m];
			if (m >= diam[k][0])
			{
				int const newVal = d[k][m - diam[k][0]] + diam[k][1];
				if (d[k + 1][m] < newVal) d[k + 1][m] = newVal;
			}
		}
	}
	// 判断选择
	m = C;
	for (k = n - 1; k >= 0; --k)
	{
		if (d[k + 1][m] != d[k][m]) { sln[k] = 1; m -= diam[k][0]; }
		else sln[k] = 0;
	}
	// 输出结果
	printf("\nMaximum Value: %d", d[n][C]);
	printf("\nChoice:");
	for (k = 0; k < n; ++k)
		printf("%2d", sln[k]);
	printf("\n\n");
	return 0;
}
