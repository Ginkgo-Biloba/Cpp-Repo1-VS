#include "leetcode.hpp"

/* 77. 组合

给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

示例:

输入: n = 4, k = 2
输出:
[
	[2,4],
	[3,4],
	[2,3],
	[1,2],
	[1,3],
	[1,4],
]
*/

class Solution
{
	vector<vector<int>> ans;
	vector<int> cur;

	void dfs(int n, int k)
	{
		if (k == 0)
		{
			ans.push_back(cur);
			return;
		}
		if (k > n)
			return;
		for (; n >= 1; --n)
		{
			cur.push_back(n);
			dfs(n - 1, k - 1);
			cur.pop_back();
		}
	}

public:
	vector<vector<int>> combine(int n, int k)
	{
		cur.reserve(k);
		dfs(n, k);
		vector<vector<int>> R;
		R.swap(ans);
		return R;
	}
};


int main()
{
	Solution s;
	output(s.combine(4, 2), "Combinations");
}
