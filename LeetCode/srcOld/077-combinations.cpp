#include "../srcOld/utility.hpp"

void combine_dfs(int const n, int const k, int count, int idx, \
	vector<int>& cur, vector<vector<int>>& ans)
{
	if (k == count)
	{
		ans.push_back(cur);
		return;
	}

	if ((k - count) > (n - idx)) // 加完数量还不够
		return;

	for (; idx < n; ++idx)
	{
		cur.push_back(idx + 1); // 题目第 1 个数是 1，不是 0
		combine_dfs(n, k, count + 1, idx + 1, cur, ans);
		cur.pop_back();
	}
}

vector<vector<int>> combine(int n, int k)
{
	vector<int> cur;
	vector<vector<int>> ans;
	if (k > 0)
		combine_dfs(n, k, 0, 0, cur, ans);
	return ans;
}

int main()
{
	vector<vector<int>> grid = combine(5, 3);
	output(grid, "combine");
}
