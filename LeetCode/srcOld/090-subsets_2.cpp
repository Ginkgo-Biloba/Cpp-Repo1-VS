#include "../src/utility.hpp"

void subsets_bfs(vector<int> const& nums, int k, int const len, \
	vector<int>& cur, vector<vector<int>>& ans)
{
	if (k == len)
		return;

	for (; k < len; ++k)
	{
		cur.push_back(nums[k]);
		ans.push_back(cur);
		subsets_bfs(nums, k + 1, len, cur, ans);
		cur.pop_back();
	}
}

vector<vector<int>> subsetsWithDup(vector<int>& nums)
{
	size_t const len = nums.size();
	vector<vector<int>> ans;
	vector<int> cur;
	ans.push_back(cur);
	std::sort(nums.begin(), nums.end());

	for (size_t i = 0; i < len;)
	{
		size_t count = 1; // 有这么多个重复元素
		while ((i + count < len) && (nums[i] == nums[i + count]))
			++count;
		size_t const prevLen = ans.size();
		for (size_t p = 0; p < prevLen; ++p)
		{
			cur = ans[p];
			for (size_t c = 0; c < count; ++c)
			{
				cur.push_back(nums[i]);
				ans.push_back(cur);
			}
		}
		i += count;
	}

	return ans;
}


int main()
{
	vector<int> digits = { 1, 2, 2, 2 };
	vector<vector<int>> grid = subsetsWithDup(digits);
	output(grid, "subsetsWithDup");
}
