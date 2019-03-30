#include <vector>
#include <cstdio>

// 只能买一次
int maxProfit(std::vector<int> const& prices)
{
	size_t const len = static_cast<int>(prices.size());
	if (len < 2u) return 0;
	int ans = 0, minp = prices[0];

	for (size_t i = 1; i < len; i++)
	{
		if (prices[i] < minp)
			minp = prices[i];
		else
		{
			int const cur = prices[i] - minp;
			if (ans < cur) ans = cur;
		}
	}

	return ans;
}


int main()
{
	std::vector<int> prices = { 3, 2, 6, 5, 0, 3 };
	int ans = maxProfit(prices);
	printf("ans = %d\n", ans);
	return 0;
}

