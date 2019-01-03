#include <vector>
#include <iostream>
#include <algorithm>
typedef std::vector<int> vint;

void backtrack(std::vector<vint>& ans, vint& cur, vint const& nums, size_t pos, int rest)
{
	if (rest < 0); // 什么也不做
	else if (rest == 0) ans.push_back(cur);
	else for (size_t i = pos; i < nums.size(); i++)
	{
		cur.push_back(nums[i]);
		backtrack(ans, cur, nums, i, rest - nums[i]); // 不是 i + 1 因为可以用相同的数
		cur.pop_back();
	}
}

std::vector<vint> combinationSum(vint& nums, int target)
{
	std::vector<vint> ans;
	vint cur;
	std::sort(nums.begin(), nums.end());
	backtrack(ans, cur, nums, 0u, target);
	return ans;
}

int main()
{
	vint nums = {2, 3, 6, 7};
	int target = 7;
	std::vector<vint> ans = combinationSum(nums, target);
	for (vint const& vi : ans)
	{
		for (int const& i : vi)
			std::cout << i << ", ";
		std::cout << "\b\b;\n";
	}
	return 0;
}