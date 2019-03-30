#include "../srcOld/utility.hpp"

/* 324. 摆动排序 II
 * 给定一个无序的数组 nums，将它重新排列成
 * nums[0] < nums[1] > nums[2] < nums[3]...
 * 的顺序。
 * 示例 1:
 *  - 输入: nums = [1, 5, 1, 1, 6, 4]
 *  - 输出: 一个可能的答案是 [1, 4, 1, 5, 1, 6]
 * 说明: 你可以假设所有输入都会得到有效的结果。
 * 进阶: 你能用 O(n) 时间复杂度和 / 或原地 O(1) 额外空间来实现吗？
 */

// https://leetcode.com/problems/wiggle-sort-ii/discuss/77688/O(n)%2BO(1)-after-median-without-Virtual-Indexing-%3A-)
// 抄的
void wiggleSort(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	int L, M, R = len / 2, mid;
	std::nth_element(nums.begin(), nums.begin() + R, nums.end());

	mid = nums[R];
	R = (len - 1) & ~1; M = R; L = 1;
	for (int i = 0; i < len; ++i)
	{
		if (nums[M] < mid)
		{
			std::swap(nums[M], nums[R]);
			M -= 2;
			R -= 2;
			if (M < 0)
				M = (len & ~1) - 1;
		}
		else if (nums[M] > mid)
		{
			std::swap(nums[M], nums[L]);
			L += 2;
		}
		else
		{
			M -= 2;
			if (M < 0)
				M = (len & ~1) - 1;
		}
	}
}

int main()
{
	// 1 6 1 5 1 4 1
	vector<int> nums = { 1, 5, 1, 1, 6, 4, 9 };
	wiggleSort(nums);
	output(nums, "wiggle sort");
}

