#include "leetcode.hpp"

/* 398. 随机数索引

给定一个可能含有重复元素的整数数组，要求随机输出给定的数字的索引。
您可以假设给定的数字一定存在于数组中。
注意：
数组大小可能非常大。 使用太多额外空间的解决方案将不会通过测试。

示例:
int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);
// pick(3) 应该返回索引 2,3 或者 4。每个索引的返回概率应该相等。
solution.pick(3);
// pick(1) 应该返回 0。因为只有nums[0]等于1。
solution.pick(1);
*/

// 讨论里面说应该用蓄水池抽样

class Solution
{
	vector<int> idx;
	vector<int>& nums;
	std::mt19937 mt;
public:
	Solution(vector<int>& _nums)
		: nums(_nums)
	{
		std::random_device rd;
		mt.seed(rd());
		idx.resize(nums.size());
		std::iota(idx.begin(), idx.end(), 0);
		std::sort(idx.begin(), idx.end(),
			[this](int x, int y) -> bool
		{
			return nums[x] < nums[y];
		});
		std::sort(nums.begin(), nums.end());
	}

	int pick(int target)
	{
		// 题目说了保证 target 在里面
		ptrdiff_t x = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
		ptrdiff_t y = std::upper_bound(nums.begin(), nums.end(), target) - nums.begin();
		x += static_cast<ptrdiff_t>(mt() % (y - x));
		return idx[x];
	}
};



int main()
{
	vector<int> nums = { 1, 2, 3, 3, 3 };
	Solution sln(nums);
	OutExpr(sln.pick(1), "%d");
	OutExpr(sln.pick(3), "%d");
	OutExpr(sln.pick(3), "%d");
	OutExpr(sln.pick(3), "%d");
	OutExpr(sln.pick(3), "%d");
	OutExpr(sln.pick(3), "%d");
}
