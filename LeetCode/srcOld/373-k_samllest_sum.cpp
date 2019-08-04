#include "leetcode.hpp"

/* 373. 查找和最小的K对数字

给定两个以升序排列的整形数组 nums1 和 nums2, 以及一个整数 k。
定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2。
找到和最小的 k 对数字 (u1,v1), (u2,v2) ... (uk,vk)。

示例 1:
输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [1,2],[1,4],[1,6]
解释: 返回序列中的前 3 对数：
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

示例 2:
输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出: [1,1],[1,1]
解释: 返回序列中的前 2 对数：
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

示例 3:
输入: nums1 = [1,2], nums2 = [3], k = 3
输出: [1,3],[2,3]
解释: 也可能序列中所有的数对都被返回:[1,3],[2,3]
*/

struct SUM
{
	int val, a, ib;

	SUM(int A, int B, int iB)
		: val(A + B), a(A), ib(iB)
	{}

	bool operator <(SUM const& rhs) const
	{
		return rhs.val < val; // 因为要最小的值
	}
};


vector<vector<int>> kSmallestPairs(vector<int>& a, vector<int>& b, int k)
{
	vector<vector<int>> ans;
	vector<int> elem(2);
	int blen = static_cast<int>(b.size());
	if (blen == 0 || k == 0)
		return ans;
	std::priority_queue<SUM> qs;
	for (int A : a)
		qs.push(SUM(A, b[0], 0));

	for (; k > 0 && !qs.empty(); --k)
	{
		SUM cur = qs.top();
		qs.pop();
		elem[0] = cur.a;
		elem[1] = b[cur.ib];
		ans.push_back(elem);
		++(cur.ib);
		if (cur.ib < blen)
		{
			cur.val = b[cur.ib] + cur.a;
			qs.push(cur);
		}
	}

	return ans;
}


int main()
{
	vector<int> a = { 1, 7, 11 };
	vector<int> b = { 2, 4, 6 };
	vector<vector<int>> d = kSmallestPairs(a, b, 94);
	output(d, "kSmallestPairs");
}
