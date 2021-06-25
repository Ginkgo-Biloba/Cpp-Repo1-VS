#include "leetcode.hpp"

/* 1782. 统计点对的数目

给你一个无向图，无向图由整数 n，表示图中节点的数目，和 edges 组成，其中 edges[i] = [ui, vi] 表示 ui 和 vi 之间有一条无向边。
同时给你一个代表查询的整数数组 queries 。

第 j 个查询的答案是满足如下条件的点对 (a, b) 的数目：
	a < b
	cnt 是与 a 或者 b 相连的边的数目，且 cnt 严格大于 queries[j] 。

请你返回一个数组 answers ，其中 answers.length == queries.length 且 answers[j] 是第 j 个查询的答案。

请注意，图中可能会有 重复边 。

示例 1：
https://assets.leetcode.com/uploads/2021/02/11/screenshot-from-2021-02-11-23-07-35.png
https://pic.leetcode-cn.com/1614828447-GMnLVg-image.png
输入：n = 4,
edges = [[1,2],[2,4],[1,3],[2,3],[2,1]],
queries = [2,3]
输出：[6,5]
解释：每个点对中，与至少一个点相连的边的数目如上图所示。

示例 2：

输入：n = 5,
edges = [[1,5],[1,5],[3,4],[2,5],[1,3],[5,1],[2,3],[2,5]],
queries = [1,2,3,4,5]
输出：[10,10,9,8,6]

提示：
	2 <= n <= 2 * 10^4
	1 <= edges.length <= 10^5
	1 <= ui, vi <= n
	ui != vi
	1 <= queries.length <= 20
	0 <= queries[j] < edges.length
*/

// https://leetcode.com/problems/count-pairs-of-nodes/discuss/1096740/C%2B%2BJavaPython3-Two-Problems-O(q-*-(n-%2B-e))
// 抄的
vector<int> countPairs(int n,
	vector<vector<int>>& edges, vector<int>& queries)
{
	vector<int> cnt(n + 1), sorted_cnt(n + 1), res;
	vector<unordered_map<int, int>> shared(n + 1);
	for (auto& e : edges)
	{
		sorted_cnt[e[0]] = cnt[e[0]] = cnt[e[0]] + 1;
		sorted_cnt[e[1]] = cnt[e[1]] = cnt[e[1]] + 1;
		++shared[min(e[0], e[1])][max(e[0], e[1])];
	}
	sort(sorted_cnt.begin(), sorted_cnt.end());
	for (auto& q : queries)
	{
		res.push_back(0);
		for (int i = 1, j = n; i < j;)
			if (q < sorted_cnt[i] + sorted_cnt[j])
				res.back() += (j--) - i;
			else
				++i;
		for (auto i = 1; i <= n; ++i)
			for (auto const& it : shared[i])
			{
				int j = it.first;
				int c = it.second;
				if (q < cnt[i] + cnt[j] && q + c >= cnt[i] + cnt[j])
					--(res.back());
			}
	}
	return res;
}


int main()
{}
