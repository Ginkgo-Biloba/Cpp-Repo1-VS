#include "leetcode.hpp"

/* 581. 最短无序连续子数组

给定一个整数数组，你需要寻找一个连续的子数组，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

你找到的子数组应是最短的，请输出它的长度。

示例 1:
输入: [2, 6, 4, 8, 10, 9, 15]
输出: 5
解释: 你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。

说明 :
	输入的数组长度范围在 [1, 10,000]。
	输入的数组可能包含重复元素 ，所以升序的意思是<=。
*/

int findUnsortedSubarray(vector<int>& nums)
{
	int L = 0, R = static_cast<int>(nums.size());
	if (R < 2)
		return 0;

	vector<int> s = nums;
	std::sort(s.begin(), s.end());
	for (; L < R && s[L] == nums[L]; ++L)
		;
	for (; L < R && s[R - 1] == nums[R - 1]; --R)
		;
	return R - L;
}

// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/discuss/103066/Ideas-behind-the-O(n)-two-pass-and-one-pass-solutions
// 抄的
int findUnsortedSubarray2(vector<int>& nums)
{
	int vmax = INT_MIN, vmin = INT_MAX;
	int imax = -1, imin = 0;
	int L = 0, R = static_cast<int>(nums.size()) - 1;
	for (; R >= 0; ++L, --R)
	{
		if (vmax > nums[L])
			imax = L;
		else
			vmax = nums[L];

		if (vmin < nums[R])
			imin = R;
		else
			vmin = nums[R];
	}
	return (imax - imin + 1);
}


int main()
{
	vector<int> nums = { 2, 6, 4, 8, 10, 9, 15 };
	OutExpr(findUnsortedSubarray2(nums), "%d");
}
