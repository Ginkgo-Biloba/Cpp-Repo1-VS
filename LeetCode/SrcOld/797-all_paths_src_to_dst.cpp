#include "leetcode.hpp"

/* 797. 所有可能的路径

给一个有 n 个结点的有向无环图，找到所有从 0 到 n-1 的路径并输出（不要求按顺序）

二维数组的第 i 个数组中的单元都表示有向图中 i 号结点所能到达的下一些结点（译者注：有向图是有方向的，即规定了a→b你就不能从b→a）空就是没有下一个结点了。

示例:
输入: [[1,2], [3], [3], []]
输出: [[0,1,3],[0,2,3]]
解释: 图是这样的:
0--->1
|    |
v    v
2--->3
这有两条路: 0 -> 1 -> 3 和 0 -> 2 -> 3.

提示:
	结点的数量会在范围 [2, 15] 内。
	你可以把路径以任意顺序输出，但在路径内的结点的顺序必须保证。
*/

class Solution
{
	vector<vector<int>> G, A;
	vector<int> P;
	int N;

	void dfs(int cur)
	{
		P.push_back(cur);
		if (cur == N - 1)
			A.push_back(P);
		else
		{
			int len = static_cast<int>(G[cur].size());
			int const* ptr = G[cur].data();
			for (int i = 0; i < len; ++i)
				dfs(ptr[i]);
		}
		P.pop_back();
	}

public:
	vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
	{
		G.swap(graph);
		N = static_cast<int>(G.size());
		P.reserve(N);
		dfs(0);
		vector<vector<int>> ans;
		ans.swap(A);
		return ans;
	}
};

int main()
{
	Solution s;
	vector<vector<int>> g = { { 1, 2 }, { 3 }, { 3 }, {} };
	output(s.allPathsSourceTarget(g));
}
