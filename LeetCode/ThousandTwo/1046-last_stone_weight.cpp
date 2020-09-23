#include "leetcode.hpp"

/* 1046. 最后一块石头的重量

有一堆石头，每块石头的重量都是正整数。

每一回合，从中选出两块最重的石头，然后将它们一起粉碎。
假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：
	如果 x == y，那么两块石头都会被完全粉碎；
	如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。

最后，最多只会剩下一块石头。返回此石头的重量。如果没有石头剩下，就返回 0。

提示：
	1 <= stones.length <= 30
	1 <= stones[i] <= 1000
*/


int lastStoneWeight(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int x, y;
	make_heap(A.begin(), A.end());
	while (len > 1)
	{
		x = A[0];
		pop_heap(A.begin(), A.end());
		A.pop_back();
		y = A[0];
		pop_heap(A.begin(), A.end());
		A.pop_back();
		x -= y;
		if (x > 0)
		{
			--len;
			A.push_back(x);
			push_heap(A.begin(), A.end());
		}
		else
			len -= 2;
	}
	return A.empty() ? 0 : A[0];
}


int main()
{
	vector<int> a = { 2, 7, 4, 1, 8, 1 };
	OutExpr(lastStoneWeight(a), "%d");
}
