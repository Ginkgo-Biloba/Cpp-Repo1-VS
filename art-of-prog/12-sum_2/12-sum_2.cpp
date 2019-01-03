#include <cstdio>
#include <cstdlib>

/**< 寻找和为定值的 2 个数 */
// Ref: http://taop.marchtea.com/02.02.html

// 两端扫描，不包括 arr[n]
void fs2(int const* arr, int const& n, int const& sum)
{
	// 先排序（这里没写）
	int k = 0; int m = n - 1;
	bool has2 = false;
	while (k < m)
	{
		int s = arr[k] + arr[m];
		if (s == sum)
		{
			printf("\n(%d)[%d] + (%d)[%d] = (%d)", arr[k], k, arr[m], m, sum);
			has2 = true;
		}
		if (s < sum) ++k;
		else --m;
	}
	if (!has2)
		printf("\n? + ? = %d", sum);
}

int main()
{
	int const arr[] = { 1, 2, 4, 11, 14, 17 };
	fs2(arr, (int)(sizeof(arr) / sizeof(int)), 18);
	printf("\n\n");
	return 0;
}
