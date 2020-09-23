#include "leetcode.hpp"

/* 1552. 两球之间的磁力

在代号为 C-137 的地球上，Rick 发现如果他将两个球放在他新发明的篮子里，它们之间会形成特殊形式的磁力。
Rick 有 n 个空的篮子，第 i 个篮子的位置在 position[i] ，Morty 想把 m 个球放到这些篮子里，使得任意两球间 最小磁力 最大。

已知两个球如果分别位于 x 和 y ，那么它们之间的磁力为 |x - y| 。

给你一个整数数组 position 和一个整数 m ，请你返回最大化的最小磁力。

示例 1：
https://assets.leetcode.com/uploads/2020/08/11/q3v1.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/16/q3v1.jpg
输入：position = [1,2,3,4,7], m = 3
输出：3
解释：将 3 个球分别放入位于 1，4 和 7 的三个篮子，两球间的磁力分别为 [3, 3, 6]。最小磁力为 3 。我们没办法让最小磁力大于 3 。

示例 2：
输入：position = [5,4,3,2,1,1000000000], m = 2
输出：999999999
解释：我们使用位于 1 和 1000000000 的篮子时最小磁力最大。

提示：
	n == position.length
	2 <= n <= 10^5
	1 <= position[i] <= 10^9
	所有 position 中的整数 互不相同 。
	2 <= m <= position.length
*/


int maxDistance(vector<int>& A, int num)
{
	size_t len = A.size();
	sort(A.begin(), A.end());

	int a = 1, b = A.back();
	while (a < b)
	{
		int mid = (a + b + 1) / 2;
		int cur = 1, pre = A[0];
		for (size_t i = 1;
			i < len && cur < num;
			++i)
		{
			if (A[i] - pre < mid)
				continue;
			pre = A[i];
			cur += 1;
		}
		if (cur == num)
			a = mid;
		else
			b = mid - 1;
	}
	return a;
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 4, 7 },
		b = { 5, 4, 3, 2, 1, 1000000000 };
	OutExpr(maxDistance(a, 3), "%d");
	OutExpr(maxDistance(b, 2), "%d");
}
