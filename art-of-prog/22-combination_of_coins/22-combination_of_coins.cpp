#include <cstdio>
#include <cstring>
#include <vector>
typedef std::vector<int> vi;

/**< 硬币组合 */
// Ref: http://blog.csdn.net/lsjseu/article/details/11583513
/* 将一个较大的钱，不超过1000000 (10^6) 的人民币兑换成数量不限的 100、50、10、5、2、1 的组合 */
int nCoins1(int const& V)
{
	int const n = 7;
	int coins[n] = { 1, 2, 5, 10, 20, 50, 100 }; // 面值
	int* d; int k, v;
	d = new int[V + 1];
	// 用第 0 张，即面值为 1 元的都只有一种
	for (v = 0; v <= V; ++v) d[v] = 1;
	for (k = 1; k < n; ++k)
	{
		for (v = 0; v <= V; ++v) // 使用更新后的值
			if (v >= coins[k])  // 算进去，或不算进去
				d[v] += d[v - coins[k]];
	}
	int rst = d[V]; // 记住结果
	delete[] d;
	return rst;
}

// 第二种方案，带输出，类似于 2-3 FixedSumK
void coin2_base(vi& vec, int curV, size_t iCoin, int& nMtd, vi const& coins, int const& V)
{
	if (curV == V) // 输出
	{
		++nMtd;
		printf("\n%8s %3d: ", "Solution", nMtd);
		for (size_t k = 0; k < vec.size() - 1; ++k)
			printf("%d, ", vec[k]);
		printf("%d", vec.back());
		return;
	}
	for (size_t k = iCoin; k < coins.size(); ++k) // 统计到第 iCoin 个硬币
	{
		if (curV + coins[k] <= V)
		{
			vec.push_back(coins[k]);
			coin2_base(vec, curV + coins[k], k, nMtd, coins, V); // k 表示可以重复
			vec.pop_back();
		}
		else break;
	}
}

int nCoins2(int const& V)
{
	if (V <= 0) return 0;
	int nMtd = 0;
	vi const coins = { 1, 2, 5, 10, 20, 50, 100 };
	vi vec;
	printf("\nCoins: ");
	for (size_t k = 0; k < coins.size() - 1; ++k)
		printf("%d, ", coins[k]);
	printf("%d", coins.back());
	printf("\nValue: %d", V);
	coin2_base(vec, 0, 0u, nMtd, coins, V);
	// printf("\nTotal: %d", nMtd);
	return nMtd;
}

int main()
{
	printf("%d\n", nCoins1(23));
	nCoins2(23);
	printf("\n\n");
	return 0;
}
