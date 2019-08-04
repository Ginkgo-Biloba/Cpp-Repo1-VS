#include "leetcode.hpp"

/* 316. 去除重复字母
 * 给定一个仅包含小写字母的字符串，去除字符串中重复的字母，使得每个字母只出现一次。
 * 需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
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

