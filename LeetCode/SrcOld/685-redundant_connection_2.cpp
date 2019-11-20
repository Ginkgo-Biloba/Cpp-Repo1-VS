#include "leetcode.hpp"

/* 685. 冗余连接 II

在本问题中，有根树指满足以下条件的有向图。
该树只有一个根节点，所有其他节点都是该根节点的后继。
每一个节点只有一个父节点，除了根节点没有父节点。

输入一个有向图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。
附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。

结果图是一个以边组成的二维数组。
每一个边的元素是一对 [u, v]，用以表示有向图中连接顶点 u and v和顶点的边，其中父节点u是子节点v的一个父节点。

返回一条能删除的边，使得剩下的图是有N个节点的有根树。
若有多个答案，返回最后出现在给定二维数组的答案。

示例 1:
输入: [[1,2], [1,3], [2,3]]
输出: [2,3]
解释: 给定的有向图如下:
|   1
|  / \
| v   v
| 2-->3

示例 2:
输入: [[1,2], [2,3], [3,4], [4,1], [1,5]]
输出: [4,1]
解释: 给定的有向图如下:
| 5 <- 1 -> 2
|      ^    |
|      |    v
|      4 <- 3

注意:
	二维数组大小的在3到1000范围内。
	二维数组中的每个整数在1到N之间，其中 N 是二维数组的大小。
*/


// https://leetcode.com/problems/redundant-connection-ii/discuss/278105/topic
// 抄的
class Solution
{
	vector<vector<int>> edges;
	vector<int> parent;
	int len;

public:
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& _edges)
	{
		vector<int> A, B, C;
		edges.swap(_edges);
		len = static_cast<int>(edges.size());
		parent.resize(len + 1);
		memset(parent.data(), 0, (len + 1) * sizeof(int));

		// 检查是否有个节点有两个父亲
		for (vector<int>& e : edges)
		{
			if (parent[e[1]] == 0)
				parent[e[1]] = e[0];
			else
			{
				A.push_back(parent[e[1]]);
				A.push_back(e[1]);
				B = e;
				e[1] = 0; // 改向闲置的节点 0
			}
		}

		// 并查集
		for (int i = 1; i <= len; ++i)
			parent[i] = i;
		for (vector<int>& e : edges)
		{
			int F = e[0], T = e[1];
			if (T == 0)
				continue;
			while (parent[F] != F) F = parent[F];
			/* 如果有两个候选 A B 的话，已经在上面一步中把靠后的 B 指向 0 了，而且跳过了 0。
			所以后面那个 B 是不会出现成环的情况的。
			如果还出现成环，肯定是因为 A 有问题，删 A。如果没有成环，删靠后的e */
			if (F == T)
				return A.empty() ? e : A;
			parent[T] = F;
		}
		return B;
	}
};


int main()
{
	vector<vector<int>>
		edges1 = { { 1, 2 }, { 1, 3 }, { 2, 3 } },
		edges2 = { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 1 }, { 1, 5 } };
	Solution s;
	output(s.findRedundantDirectedConnection(edges1),
		"Redundant Connection II");
	output(s.findRedundantDirectedConnection(edges2),
		"Redundant Connection II");
}
