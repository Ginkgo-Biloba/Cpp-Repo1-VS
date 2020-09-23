#include "leetcode.hpp"

/* 746. 使用最小花费爬楼梯

数组的每个索引做为一个阶梯，第i个阶梯对应着一个非负数的体力花费值 cost[i](索引从0开始)。
每当你爬上一个阶梯你都要花费对应的体力花费值，然后你可以选择继续爬一个阶梯或者爬两个阶梯。
您需要找到达到楼层顶部的最低花费。
在开始时，你可以选择从索引为 0 或 1 的元素作为初始阶梯。

示例 1:
输入: cost = [10, 15, 20]
输出: 15
解释: 最低花费是从cost[1]开始，然后走两步即可到阶梯顶，一共花费15。

示例 2:
输入: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
输出: 6
解释: 最低花费方式是从cost[0]开始，逐个经过那些1，跳过cost[3]，一共花费6。

注意：
	cost 的长度将会在 [2, 1000]。
	每一个 cost[i] 将会是一个Integer类型，范围为 [0, 999]。
*/


// 想像成下楼梯就是经典问题了
int minCostClimbingStairs(vector<int>& cost)
{
	int C[3], N = static_cast<int>(cost.size());
	C[2] = cost[N - 1];
	C[1] = cost[N - 2];
	for (N -= 3; N >= 0; --N)
	{
		C[0] = std::min(C[1], C[2]) + cost[N];
		C[2] = C[1];
		C[1] = C[0];
	}
	return std::min(C[1], C[2]);
}


int main()
{
	vector<int> cost1 = { 10, 15, 20 };
	vector<int> cost2 = { 1, 100, 1, 1, 1, 100, 1, 1, 100, 1 };
	OutExpr(minCostClimbingStairs(cost1), "%d");
	OutExpr(minCostClimbingStairs(cost2), "%d");
}
