#include "leetcode.hpp"

/* 216. 组合总和 III

找出所有相加之和为 n 的 k 个数的组合。
组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。

说明：
	所有数字都是正整数。
	解集不能包含重复的组合。

示例 1:
输入: k = 3, n = 7
输出: [[1,2,4]]

示例 2:
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
*/

class Solution
{
	vector<vector<int>> ans;
	vector<int> cur;

	void dfs(int k, int n, int s)
	{
		if (k == 0)
		{
			if (n == 0)
				ans.push_back(cur);
			return;
		}
		if ((n > s * k) || (k > s))
			return;
		for (; s >= 1; --s)
		{
			cur.push_back(s);
			dfs(k - 1, n - s, s - 1);
			cur.pop_back();
		}
	}

public:
	vector<vector<int>> combinationSum3(int k, int n)
	{
		vector<vector<int>> R;
		dfs(k, n, 9);
		R.swap(ans);
		return R;
	}
};


int main()
{
	Solution s;
	output(s.combinationSum3(3, 7), "Combination Sum III");
	output(s.combinationSum3(3, 9), "Combination Sum III");
}
