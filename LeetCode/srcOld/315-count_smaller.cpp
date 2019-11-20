#include "leetcode.hpp"

/* 315. 计算右侧小于当前元素的个数

给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。

示例:
输入: [5,2,6,1]
输出: [2,1,1,0] 
解释:
5 的右侧有 2 个更小的元素 (2 和 1).
2 的右侧仅有 1 个更小的元素 (1).
6 的右侧有 1 个更小的元素 (1).
1 的右侧有 0 个更小的元素.
*/

// https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/138154/The-C%2B%2B-merge-sort-template-for-pairs-'i'-'j'-problem
// 抄的
typedef vector<pair<int, int>>::iterator iterator;

void sortCount(iterator left, iterator right, vector<int>& count)
{
	if (left + 1 >= right) // 空集合或者只有一个数字
		return;

	iterator mid = left + (right - left) / 2;
	sortCount(left, mid, count);
	sortCount(mid, right, count);
	for (iterator L = left, M = mid; L < mid; ++L)
	{
		// 有数字从右边移到左边了
		while ((M < right) && (L->first > M->first)) ++M;
		count[L->second] += static_cast<int>(M - mid);
	}
	std::inplace_merge(left, mid, right);
}


vector<int> countSmaller(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	vector<pair<int, int>> validx;
	validx.reserve(len);
	for (int i = 0; i < len; ++i)
		validx.emplace_back(nums[i], i);
	vector<int> count(len);
	sortCount(validx.begin(), validx.end(), count);
	return count;
}


int main()
{
	vector<int> nums = { 5, 2, 6, 1 };
	vector<int> count = countSmaller(nums);
	output(count, "countSmaller");
}

