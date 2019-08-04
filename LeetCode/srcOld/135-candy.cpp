#include "leetcode.hpp"

/* 老师想给孩子们分发糖果。
 * 有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。
 * 你需要按照以下要求，帮助老师给这些孩子分发糖果：
 * - 每个孩子至少分配到 1 个糖果。
 * - 相邻的孩子中，评分高的孩子必须获得更多的糖果。
 * 那么这样下来，老师至少需要准备多少颗糖果呢？
 **/

 // 抄的
int candy(vector<int> const& rate)
{
	size_t const len = rate.size();
	vector<int> candies(len, 1);
	int sum = 0;

	for (size_t i = 1; i < len; ++i)
		if (rate[i] > rate[i - 1])
			candies[i] = candies[i - 1] + 1;
	for (size_t i = len - 1; i > 0; --i)
		if (rate[i - 1] > rate[i])
			candies[i - 1] = std::max(candies[i - 1], candies[i] + 1);

	for (size_t i = 0; i < len; ++i)
		sum += candies[i];
	return sum;
}


int main()
{
	vector<int> rate = { 1, 2, 2 };
	int ans = candy(rate);
	printf("%d\n", ans);
}
