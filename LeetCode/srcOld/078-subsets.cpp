#include "leetcode.hpp"

void subsets_dfs(vector<int> const& nums, int k, int const len, \
	vector<int>& cur, vector<vector<int>>& ans)
{
	if (k == len)
		return;

	for (; k < len; ++k)
	{
		cur.push_back(nums[k]);
		ans.push_back(cur);
		subsets_dfs(nums, k + 1, len, cur, ans);
		cur.pop_back();
	}
}

vector<vector<int>> subsets(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	vector<vector<int>> ans;
	vector<int> cur;
	// ans.push_back(cur);
	if (len > 0)
		subsets_dfs(nums, 0, len, cur, ans);
	return ans;
}


int main()
{
	vector<int> digits = { 1, 3, 2 };
	vector<vector<int>> grid = subsets(digits);
	output(grid, "subset");
}
