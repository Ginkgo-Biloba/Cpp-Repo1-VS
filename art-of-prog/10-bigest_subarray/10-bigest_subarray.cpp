#include <cstdio>
#include <cstring>

/**< 最大连续子数组和 */
// Ref: http://taop.marchtea.com/02.04.html
int bssa(int const* arr, int const& n, bool vbs = true, int* pB = nullptr, int* pE = nullptr)
{
	if (n < 0) return 0;
	int curS = arr[0]; // 当前和
	int maxS = arr[0]; // 最大和
	int iB = 0; int iE = 0; // [iB, iE]
	int i1 = 0;
	for (int k = 1; k < n; ++k)
	{
		if (curS < 0) // 负数提升不了和，只能抛弃
		{ curS = arr[k]; i1 = k; }
		else // 累加
			curS += arr[k];
		if (maxS < curS) // 加上有效果，则重置终点
		{ maxS = curS; iB = i1; iE = k; }
	}
	if (vbs)
	{
		printf("\nArray:\n");
		for (int k = 0; k < n; ++k) printf("%+d  ", arr[k]);
		printf("\n\nMax continuous sum of sub array:\n");
		for (int k = iB; k < iE; ++k) printf("(%+d) + ", arr[k]);
		printf("(%+d) = (%+d);  [%d -> %d]", arr[iE], maxS, iB, iE);
	}
	if (pB != nullptr) *pB = iB;
	if (pE != nullptr) *pE = iE;
	return maxS;
}

/**< 最大连续子数组积 */
// Ref: http://blog.csdn.net/martin_liang/article/details/40273547
// 需要考虑到负负得正的情况，所以需要保存最小值
int bpsa(int const* arr, int const& n, int* pB = nullptr, int* pE = nullptr)
{
	if (n < 0)
	{ return 0; }
	int minP = arr[0]; // 最小积
	int maxP = arr[0]; // 最大积
	int iB = 0; int iE = 0; // [iB, iE]
	int i1 = 0; int i2 = 0; //
	for (int k = 1; k < n; ++k)
	{
		int const p1 = arr[k] * minP;
		int const p2 = arr[k] * maxP;
		int pa = p1; int pb = p2;
		if (pa > pb) { pa = p2; pb = p1; }
		maxP = (pb > arr[k]) ? pb : arr[k];
		minP = (pa < arr[k]) ? pa : arr[k];
		if (minP == arr[k]) i1 = k;
		if (maxP == arr[k]) i2 = k; // 从这里开始
		else if (maxP == p1) // 负负得正
		{ iB = i1; iE = k; }
		if (maxP == p2) // 正数相乘
		{ iB = i2; iE = k; }
	}
	printf("\nArray:\n");
	for (int k = 0; k < n; ++k) printf("%+d  ", arr[k]);
	printf("\n\nMaximum continuous product of sub array:\n");
	for (int k = iB; k < iE; ++k) printf("(%+d) × ", arr[k]);
	printf("(%+d) = (%+d);  [%d -> %d]", arr[iE], maxP, iB, iE);
	if (pB != nullptr) *pB = iB;
	if (pE != nullptr) *pE = iE;
	return maxP;
}

/**< 最大子矩阵和 */
// Ref: http://www.cnblogs.com/tianshuai11/archive/2012/04/23/2477161.html
int bssm(int const* arr, int const& rows, int const& cols)
{
	int maxSum = arr[0];
	int maxRB = 0; int maxRE = 0; // 记录位置
	int maxCB = 0; int maxCE = 0;
	int* colSum = new int[cols]; // 列和
	for (int r1 = 0; r1 < rows; ++r1)
	{
		std::memset(colSum, 0, sizeof(int)* cols);
		// 枚举每一行到每一行
		for (int r2 = r1; r2 < rows; ++r2)
		{
			int c1, c2;
			for (c1 = 0; c1 < cols; ++c1) colSum[c1] += arr[r2 * cols + c1];
			int tmax = bssa(colSum, cols, false, &c1, &c2);
			if (maxSum < tmax)
			{
				maxSum = tmax;
				maxRB = r1; maxRE = r2;
				maxCB = c1; maxCE = c2;
			}
		}
	}
	printf("\nArray (%d × %d):\n", rows, cols);
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c) printf("%+4d  ", arr[r * cols + c]);
		printf("\n");
	}
	printf("\nMaximum sum of sub Array [(%d, %d) -> (%d, %d)]: %d\n",\
		maxRB, maxCB, maxRE, maxCE, maxSum);
	for (int r = maxRB; r <= maxRE; ++r)
	{
		for (int c = maxCB; c <= maxCE; ++c) printf("%+4d  ", arr[r * cols + c]);
		printf("\n");
	}
	delete[] colSum;
	return maxSum;
}

int main()
{
	int const n = 8;
	int const m = 4;
	int const arr[n] = { 1, -2, -3, -10, 4, 7, -2, -5 };
	bssa(arr, n);
	printf("\n\n");
	bpsa(arr, n);
	printf("\n\n");
	int const mrr[] = { +0, -2, +7, -3, +9, +2, -6, -2, -4, +1, -4, +1, -1, 8, 0, -2 };
	bssm(mrr, m, m);
	printf("\n\n");
	return 0;
}
