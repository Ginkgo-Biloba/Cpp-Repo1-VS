#include <cstdio>
#include <cstring>
#include <cstdlib>

/**< 问题：最长递增子序列 */
// Ref: http://blog.csdn.net/joylnwang/article/details/6766317
// Ref: http://qiemengdao.iteye.com/blog/1660229
/* 给定一个长度为 N 的数组 a0, a1, a2, ..., an - 1，找出一个最长的单调递增子序列
 * 递增的意思是对于任意的 i < j，都满足 ai < aj，此外子序列的意思是不要求连续，顺序不乱即可。
 * 例如，长度为 6 的数组 A = {5, 6, 7, 1, 2, 8}，则其最长的单调递增子序列为 {5, 6, 7, 8}，长度为 4。 */

int LIncSeq1(int const* inArr, int const len)
{
	if (len < 0) return len;
	int* const dp = new int[len];
	int* const pre = new int[len]; // 储存开始位置
	for (int k = 0; k < len; ++k) { dp[k] = 1; pre[k] = k; }

	// 寻找以 k 为末尾的最长递增子序列
	for (int k = 1; k < len; ++k)
		for (int m = 0; m < k; ++m)
		{
			if (inArr[m] < inArr[k] && dp[k] < dp[m] + 1)
			{
				dp[k] = dp[m] + 1;
				pre[k] = m;
			}
		}

	int liss = 1; int iE = 0; // 末尾
	for (int k = 1; k < len; ++k)
		if (liss < dp[k])
		{
			liss = dp[k];
			iE = k;
		}
	int* rst = new int[liss];
	int pos = liss - 1;
	while (pre[iE] != iE)
	{
		rst[pos] = inArr[iE];
		--pos;
		iE = pre[iE];
	}
	rst[pos] = inArr[iE];

	// 输出原始数组和结果
	printf("\nArray (%d):\n", len);
	for (int k = 0; k < len; ++k)
		printf("  %+d", inArr[k]);;
	printf("\nLongest Increase Sub-Sequence (%d):\n", liss);
	for (int k = 0; k < liss; ++k)
		printf("  %+d", rst[k]);

	delete[] dp; delete[] pre; delete[] rst;
	return liss;
}

int main()
{
	int const arr1[] = { 35, 36, 39, 3, 15, 27, 6, 42 };
	int const n1 = sizeof(arr1) / sizeof(arr1[0]);
	LIncSeq1(arr1, n1);
	printf("\n");
	return 0;
}
