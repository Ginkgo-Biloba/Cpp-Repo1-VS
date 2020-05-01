#include "leetcode.hpp"

/* 1409. 查询带键的排列

给你一个待查数组 queries ，数组中的元素为 1 到 m 之间的正整数。
请你根据以下规则处理所有待查项 queries[i]（从 i=0 到 i=queries.length-1）：
	一开始，排列 P=[1,2,3,...,m]。
	对于当前的 i ，请你找出待查项 queries[i] 在排列 P 中的位置（下标从 0 开始），然后将其从原位置移动到排列 P 的起始位置（即下标为 0 处）。
	注意， queries[i] 在 P 中的位置就是 queries[i] 的查询结果。

请你以数组形式返回待查数组  queries 的查询结果。

示例 1：
输入：queries = [3,1,2,1], m = 5
输出：[2,1,2,1]
解释：待查数组 queries 处理如下：
对于 i=0: queries[i]=3, P=[1,2,3,4,5], 3 在 P 中的位置是 2，接着我们把 3 移动到 P 的起始位置，得到 P=[3,1,2,4,5] 。
对于 i=1: queries[i]=1, P=[3,1,2,4,5], 1 在 P 中的位置是 1，接着我们把 1 移动到 P 的起始位置，得到 P=[1,3,2,4,5] 。
对于 i=2: queries[i]=2, P=[1,3,2,4,5], 2 在 P 中的位置是 2，接着我们把 2 移动到 P 的起始位置，得到 P=[2,1,3,4,5] 。
对于 i=3: queries[i]=1, P=[2,1,3,4,5], 1 在 P 中的位置是 1，接着我们把 1 移动到 P 的起始位置，得到 P=[1,2,3,4,5] 。
因此，返回的结果数组为 [2,1,2,1] 。

示例 2：
输入：queries = [4,1,2,2], m = 4
输出：[3,1,2,0]

示例 3：
输入：queries = [7,5,5,8,3], m = 8
输出：[6,5,0,7,5]

提示：
	1 <= m <= 10^3
	1 <= queries.length <= m
	1 <= queries[i] <= m
*/


vector<int> processQueries_Org(vector<int>& queries, int m)
{
	vector<int> A, R;
	A.reserve(m);
	R.reserve(queries.size());
	for (int i = 0; i < m; ++i)
		A.push_back(i + 1);
	for (int q : queries)
	{
		int i = 0;
		for (; i < m; ++i)
		{
			if (A[i] == q)
				break;
		}
		R.push_back(i);
		for (; i > 0; --i)
			A[i] = A[i - 1];
		A[0] = q;
	}
	return R;
}


// https://leetcode-cn.com/problems/queries-on-a-permutation-with-key/solution/java-shu-zhuang-shu-zu-1ms-by-cjjohn/
// 抄的
class Solution
{
	vector<int> tree, index;

	int lowbit(int x)
	{
		return x & (-x);
	}

	// 树状数组的更新操作，将idx位置上的数加上value
	void update(int i, int val)
	{
		int len = static_cast<int>(tree.size());
		while (i < len)
		{
			tree[i] += val;
			i += lowbit(i);
		}
	}

	// 数组数组的区间查询，返回从1到idx区间的和
	int getsum(int i)
	{
		int sum = 0;
		while (i > 0)
		{
			sum += tree[i];
			i -= lowbit(i);
		}
		return sum;
	}

public:
	vector<int> processQueries(vector<int>& queries, int m)
	{
		int n = static_cast<int>(queries.size());
		vector<int> ans(n);
		// 用一个树状数组，数组从1-i的区间和getSum(i)代表在i前面有多少个数（包括自身）
		// 所以一个数对应到P中的真实索引就是getSum(i)-1
		tree.assign(n + m + 1, 0);
		// P中的1-m这m个数到其在树状数组中索引的一个映射
		index.assign(m + 1, 0);
		// 初始化，把P中m个数先放到树状数组的后m个位置
		for (int i = 1; i <= m; ++i)
		{
			index[i] = n + i;
			update(n + i, 1);
		}

		for (int i = 0; i < n; ++i)
		{
			int cur = index[queries[i]];
			ans[i] = getsum(cur) - 1;
			// 把位置indexQuery上的数给移动到起始位置，当前位置的数删除，所以需要-1
			update(cur, -1);
			// 放置这个被删除的数的起始位置
			index[queries[i]] = n - i;
			// 需要重新从起始位置开始更新树状数组
			update(n - i, 1);
		}
		return ans;
	}
};


int main()
{
	vector<int>
		a = { 3, 1, 2, 1 },
		b = { 4, 1, 2, 2 },
		c = { 7, 5, 5, 8, 3 };
	Solution s;
	output(s.processQueries(a, 5), "Queries on a Permutation With Key");
	output(s.processQueries(b, 4), "Queries on a Permutation With Key");
	output(s.processQueries(c, 8), "Queries on a Permutation With Key");
}
