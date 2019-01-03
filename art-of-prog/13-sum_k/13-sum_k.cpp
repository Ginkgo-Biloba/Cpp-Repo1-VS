#include <cstdio>
#include <cstdlib>

/**< 寻找和为定值的 k 个数 */
// 输入两个整数 n 和 sum，从数列1，2，3.......n 中随意取 k 个数，使其和等于sum，要求将其中所有的可能组合列出来。
// Ref: http://taop.marchtea.com/02.03.html
// 这里实现的是：输入一组正数，从其中找出 k 个数，其和等于 sum。本身最多 (k + 1) 层栈

// lk: 目前为止还剩几个数，ls: 还剩多大的和
// 非要使用数组而不用 list、vector (自带大小) 之类的才这么麻烦
// ln 带上引用会导致诸多问题，因为 L1 和 L2 处的 ln 必须相等
int fsk_base(int const* arr, int const& k, int const& sum, int* const sln, int ln, int& lk, int& ls)
{
	int hasLk = 0;
	// 递归出口，什么都不做，直接到最后的 return
	if (ln < lk || lk < 0 || ls < 0);
	// 输出找到的结果 (逆序)
	else if (lk > 0)
	{
		--lk; --ln;
		ls -= arr[ln]; sln[lk] = ln;
		hasLk |= fsk_base(arr, k, sum, sln, ln, lk, ls); // 放 arr[ln] // : L1
		ls += arr[ln]; ++lk;
		hasLk |= fsk_base(arr, k, sum, sln, ln, lk, ls); //不放 arr[ln] // : L2
	}
	else if (ls == 0) // lk == 0
	{
		int const k1 = k - 1;
		for (int i = 0; i < k1; ++i)
			printf("%3d[%3d] + ", arr[sln[i]], sln[i]);
		printf("%3d[%3d] {%3d} = %-6d\n", arr[sln[k1]], sln[k1], k1 + 1, sum);
		hasLk |= 1;
	}
	return hasLk;
}

void fsk(int const* arr, int const& n, int const& k, int const& sum)
{
	int hasK = 0;
	if (n >= k && k > 0 && sum > 0)
	{
		int ln = n; int lk = k; int ls = sum; // 去掉 const 属性
		int* sln = new int[k]; // 存储结果索引
		hasK = fsk_base(arr, k, sum, sln, ln, lk, ls);
		delete[] sln;
	}
	if (hasK == 0)
		printf("\n? + ... + ? {%d}= %d", k, sum);
}

int main()
{
	int const k = 5;
	int const n = 15;
	int arr[n];
	for (int i = 0; i < n; ++i) arr[i] = i + 1;
	fsk(arr, n, k, 25);
	printf("\n\n");
	return 0;
}
