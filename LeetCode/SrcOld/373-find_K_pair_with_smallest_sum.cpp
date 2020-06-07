#include "leetcode.hpp"

/* 373. 查找和最小的K对数字

给定两个以升序排列的整形数组 nums1 和 nums2, 以及一个整数 k。

定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2。

找到和最小的 k 对数字 (u1,v1), (u2,v2) ... (uk,vk)。

示例 1:
输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [1,2],[1,4],[1,6]
解释:
返回序列中的前 3 对数：
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

示例 2:
输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出: [1,1],[1,1]
解释:
返回序列中的前 2 对数：
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

示例 3:
输入: nums1 = [1,2], nums2 = [3], k = 3
输出: [1,3],[2,3]
解释: 也可能序列中所有的数对都被返回:[1,3],[2,3]
*/

struct elem
{
	int s, a, b;

	bool operator<(elem const& e) const
	{
		return s > e.s;
	}
};

vector<vector<int>> kSmallestPairs(
	vector<int>& A, vector<int>& B, int k)
{
	vector<vector<int>> R;
	if (A.empty() || B.empty())
		return R;

	int len = static_cast<int>(A.size());
	priority_queue<elem> Q;
	for (int i = 0; i < len; ++i)
		Q.push({ A[i] + B[0], i, 0 });

	len = static_cast<int>(B.size());
	for (; (k > 0) && !(Q.empty()); --k)
	{
		elem e = Q.top();
		Q.pop();
		R.push_back({ A[e.a], B[e.b] });
		if (++(e.b) < len)
		{
			e.s = A[e.a] + B[e.b];
			Q.push(e);
		}
	}
	return R;
}


int main()
{
	vector<int>
		a = { 1, 7, 11 },
		b = { 2, 4, 6 },
		c = { 1, 1, 2 },
		d = { 1, 2, 3 },
		e = { 1, 2 },
		f = { 3 };
	output(kSmallestPairs(a, b, 3), "K smallest pairs");
	output(kSmallestPairs(c, d, 2), "K smallest pairs");
	output(kSmallestPairs(e, f, 3), "K smallest pairs");
}
