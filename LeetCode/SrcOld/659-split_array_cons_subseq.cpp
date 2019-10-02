#include "leetcode.hpp"

/* 659. 分割数组为连续子序列

输入一个按升序排序的整数数组（可能包含重复数字），你需要将它们分割成几个子序列，其中每个子序列至少包含三个连续整数。返回你是否能做出这样的分割？

示例 1：
输入: [1,2,3,3,4,5]
输出: True
解释:
你可以分割出这样两个连续子序列 :
1, 2, 3
3, 4, 5

示例 2：
输入: [1,2,3,3,4,4,5,5]
输出: True
解释:
你可以分割出这样两个连续子序列 :
1, 2, 3, 4, 5
3, 4, 5

示例 3：
输入: [1,2,3,4,4,5]
输出: False

提示：
	输入的数组长度范围为 [1, 10000]
*/

// https://leetcode.com/problems/split-array-into-consecutive-subsequences/discuss/106493/C%2B%2B-O(n)-solution-two-pass
// 抄的
bool isPossible(vector<int>& nums)
{
	unordered_map<int, int> count, tails;
	for (int i : nums)
		count[i] += 1;
	for (int i : nums)
	{
		if (count[i] == 0)
			continue;
		--count[i];
		if (tails[i - 1] > 0)
		{
			--(tails[i - 1]);
			++(tails[i]);
		}
		else if (count[i + 1] && count[i + 2])
		{
			--(count[i + 1]);
			--(count[i + 2]);
			++(tails[i + 2]);
		}
		else
			return false;
	}
	return true;
}


int main()
{
	vector<int> nums = { 1, 2, 3, 3, 4, 4, 5 };
	OutExpr(boolstr[isPossible(nums)], "%s");
}
