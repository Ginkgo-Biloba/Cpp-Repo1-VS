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
		if (i != pos && nums[i] == nums[i - 1]) continue; // 跳过重复的数
		cur.push_back(nums[i]);
		backtrack(ans, cur, nums, i + 1, rest - nums[i]); // i + 1 因为不能用相同的数
		cur.pop_back();
	}
}

/* 与上一题的区别是每个元素只能用一次 */
std::vector<vint> combinationSum2(vint& nums, int target)
{
	std::vector<vint> ans;
	vint cur;
	std::sort(nums.begin(), nums.end(), [](int const& a, int const& b) -> bool \
	{ return (a > b); }); // 逆序排列先考虑组合性少的
	backtrack(ans, cur, nums, 0u, target);
	return ans;
}

int main()
{
	vint nums = {10, 1, 2, 7, 6, 1, 5};
	int target = 8;
	std::vector<vint> ans = combinationSum2(nums, target);
	for (vint const& vi : ans)
	{
		for (int const& i : vi)
			std::cout << i << ", ";
		std::cout << "\b\b;\n";
	}
	return 0;
}