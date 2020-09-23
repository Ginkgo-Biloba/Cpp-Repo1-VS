#include "leetcode.hpp"

/* 39. 组合总和

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：
	所有数字（包括 target）都是正整数。
	解集不能包含重复的组合。

示例 1:
输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
	[7],
	[2,2,3]
]

示例 2:
输入: candidates = [2,3,5], target = 8,
所求解集为:
[
	[2,2,2,2],
	[2,3,3],
	[3,5]
]
*/

class Solution
{
	vector<vector<int>> ans;
	vector<int> A, cur;
	int len;

	void dfs(int idx, int sum)
	{
		assert(sum > 0);
		cur.push_back(A[idx]);
		if (A[idx] == sum)
			ans.push_back(cur);
		else if (sum > A[idx])
			dfs(idx, sum - A[idx]);
		cur.pop_back();
		++idx;
		if (idx < len)
			dfs(idx, sum);
	}

public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
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
		a = { 2, 3, 6, 7 },
		b = { 2, 3, 5 };
	Solution s;
	output(s.combinationSum(a, 7), "Combination Sum");
	output(s.combinationSum(b, 8), "Combination Sum");
}
