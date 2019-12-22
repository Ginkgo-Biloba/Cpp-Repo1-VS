#include "leetcode.hpp"

/* 875. 爱吃香蕉的珂珂

珂珂喜欢吃香蕉。这里有 N 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
警卫已经离开了，将在 H 小时后回来。

珂珂可以决定她吃香蕉的速度 K （单位：根/小时）。
每个小时，她将会选择一堆香蕉，从中吃掉 K 根。
如果这堆香蕉少于 K 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。

珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。

返回她可以在 H 小时内吃掉所有香蕉的最小速度 K（K 为整数）。

示例 1：
输入: piles = [3,6,7,11], H = 8
输出: 4

示例 2：
输入: piles = [30,11,23,4,20], H = 5
输出: 30

示例 3：
输入: piles = [30,11,23,4,20], H = 6
输出: 23

提示：
	1 <= piles.length <= 10^4
	piles.length <= H <= 10^9
	1 <= piles[i] <= 10^9
*/

bool canEat(vector<int>& P, int K, int H)
{
	size_t N = P.size();
	int64_t t = 0;
	for (size_t i = 0; i < N; ++i)
		t += (P[i] + K - 1) / K;
	return t <= H;
}

int minEatingSpeed(vector<int>& piles, int H)
{
	int N = static_cast<int>(piles.size());
	int L = 1, R = 0, M;
	int64_t S = 0;
	for (int i = 0; i < N; ++i)
	{
		S += piles[i];
		R = std::max(R, piles[i]);
	}
	if (H == N)
		return R;
	if (S <= N)
		return 1;

	while (L < R)
	{
		M = (L + R) / 2;
		if (canEat(piles, M, H))
			R = M;
		else
			L = M + 1;
	}

	return L;
}


int main()
{
	vector<int>
		a = { 3, 6, 7, 11 },
		b = { 30, 11, 23, 4, 20 },
		c = { 30, 11, 23, 4, 20 };
	OutExpr(minEatingSpeed(a, 8), "%d");
	OutExpr(minEatingSpeed(b, 5), "%d");
	OutExpr(minEatingSpeed(c, 6), "%d");
}
