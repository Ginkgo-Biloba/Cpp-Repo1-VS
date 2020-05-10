#include "leetcode.hpp"

/* 40. 组合总和 II

给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：
	所有数字（包括目标数）都是正整数。
	解集不能包含重复的组合。

示例 1:
输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
	[1, 7],
	[1, 2, 5],
	[2, 6],
	[1, 1, 6]
]

示例 2:
输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
	[1,2,2],
	[5]
]
*/

class Solution
{
	vector<vector<int>> ans;
	vector<int> A, cur;
	int len;

	void dfs(int p, int sum)
	{
		assert(sum > 0);
		cur.push_back(A[p]);
		if (A[p] == sum)
			ans.push_back(cur);
		else if (A[p] < sum && p + 1 < len)
			dfs(p + 1, sum - A[p]);
		cur.pop_back();
		// 跳过重复的数字
		for (++p; p < len; ++p)
		{
			if (A[p - 1] != A[p])
				break;
		}
		if (p < len)
			dfs(p, sum);
	}

public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	{
		A.swap(candidates);
		len = static_cast<int>(A.size());
		sort(A.begin(), A.end(), std::greater<int>());
		cur.clear();
		if (len > 0 && target >= A[len - 1])
			dfs(0, target);
		vector<vector<int>> R;
		R.swap(ans);
		return R;
	}
};


int main()
{
	vector<int>
		a = { 10, 1, 2, 7, 6, 1, 5 },
		b = { 2, 5, 2, 1, 2 };
	Solution s;
	output(s.combinationSum2(a, 8), "Combination Sum 2");
	output(s.combinationSum2(b, 5), "Combination Sum 2");
}
