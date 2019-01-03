#include <cstdio>
#include <stack>

/**< 直方图中最大矩形面积 */
// http://www.cnblogs.com/grandyang/p/4322653.html
// http://www.cnblogs.com/lichen782/p/leetcode_Largest_Rectangle_in_Histogram.html
/* 给定直方图，每一小块的 height 由 N 个非负整数所确定，每一小块的 width 都为 1，请找出直方图中面积最大的矩形 */
/* 例如直方图中有 6 个矩形，高度分别是(2, 1, 5, 6, 2, 3)。最大的矩形面积是10 (5, 6) */

void outArr(int const* arr, int const& n, char const* info)
{
	printf(info);
	for (int k = 0; k < n - 1; ++k)
		printf("%d, ", arr[k]);
	printf("%d", arr[n - 1]);
}

int lrh1(int const* hist, int const& n)
{
	if (n <= 0) return 0;
	outArr(hist, n, "\nHistogram: ");
	int maxArea = 0;
	int iB = 0; int iE = 0;
	for (int k = 0; k < n; ++k)
	{
		if (k + 1 < n && hist[k] < hist[k + 1])
			continue;
		int minH = hist[k];
		for (int j = k; j >= 0; --j)
		{
			if (minH > hist[j]) minH = hist[j];
			int area = minH * (k - j + 1);
			if (maxArea < area)
			{
				maxArea = area;
				iB = j; iE = k;
			}
		}
	}
	printf("\nMaximum area: %d", maxArea);
	outArr(hist + iB, (iE - iB + 1), "\nRectangle: ");
	printf("  [%d, %d]", iB, iE);
	return maxArea;
}

/* 右边界有问题
int lrh2(int const* hist, int const& n)
{
	std::stack<int> indexes;
	if (n <= 0) return 0;
	outArr(hist, n, "\nHistogram: ");
	int maxArea = 0;
	int iB = 0; int iE = 0;
	int k = 0;
	while (k < n)
	{
		if (indexes.empty() || hist[indexes.top()] <= hist[k])
		{
			indexes.push(k);
			++k;
		}
		else
		{
			int t = indexes.top(); indexes.pop();
			int area = hist[t] * (indexes.empty() ? k : (k - indexes.top() - 1));
			if (maxArea < area)
			{
				maxArea = area;
				iB = indexes.empty() ? 0 : indexes.top() + 1; // indexes.top() 是矩形左边的索引，不包含
				iE = k - 1; // 要减 1，因为是 hist[k] < hist[indexes] 时才有的
			}
		}
	}
	printf("\nMaximum area: %d (%d -> %d)", maxArea, iB, iE);
	outArr(hist + iB, (iE - iB + 1), "\nRectangle: ");
	return maxArea;
}
*/

int main()
{
	int const n = 6;
	int hist[n] = { 2, 1, 5, 6, 2, 3 };
	lrh1(hist, n); printf("\n\n");
	// lrh2(hist, n); printf("\n\n");
	return 0;
}
