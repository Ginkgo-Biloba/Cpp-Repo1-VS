#include <cstdio>

// Ref: http://www.cnblogs.com/null00/archive/2012/06/20/2555541.html
/* 有 N 个鸡蛋和 M 个篮子，把鸡蛋放到篮子里，每个篮子都不能为空
 * 需要满足：任意一个小于 N 的正整数，都能由某几个篮子内蛋的数量相加的和得到
 * 写出程序，使得输入一个 (N, M)，输出所有可能的分配情况。 */

void outArr(int const* arr, int const& n, char const* info)
{
	printf(info);
	for (int k = 0; k < n - 1; ++k)
		printf("%+2d, ", arr[k]);
	printf("%+2d", arr[n - 1]);
}

void eib_base(int const& curSum, int const& iBsk, int curNum, \
	int* const bsk, int& nMtd, int const&N, int const& M)
{
	if (curSum == N && iBsk == M)
	{
		++nMtd;
		printf("\nSolution %2d: ", nMtd);
		outArr(bsk, M, "");
		return;
	}
	if (curSum > N || iBsk >= M)
		return;
	// 之后的所有篮子都添加最小鸡蛋数量，如果这都大于 N，那么肯定不符
	if ((curSum + curNum * (M - iBsk)) > N)
		return;
	// 表示之后的所有篮子都添加相应的最大值，如果这都小于 N，那么肯定也不符
	if ((curSum + (curSum + 1) * ((1 << (M - iBsk)) - 1)) < N)
		return;
	for (int j = curNum; j <= curSum + 1; ++j)
	{
		bsk[iBsk] = j;
		eib_base(curSum + j, iBsk + 1, j, bsk, nMtd, N, M);
	}
}

int eggsInBaskets(int const& N, int const& M)
{
	if (M <= 0 || N < M || N >= (1 << M))
		return 0;
	printf("\nPut %d eggs in %d baskets", N, M);
	int nMtd = 0;
	int* const bsk = new int[M]; // 存放答案
	eib_base(0, 0, 1, bsk, nMtd, N, M);
	delete[] bsk;
	return nMtd;
}

int main()
{
	eggsInBaskets(9, 5);
	printf("\n\n");
	return 0;
}
