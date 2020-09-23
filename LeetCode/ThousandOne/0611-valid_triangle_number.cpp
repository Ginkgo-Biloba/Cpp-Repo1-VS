#include "leetcode.hpp"

/* 611. 有效三角形的个数

给定一个包含非负整数的数组，你的任务是统计其中可以组成三角形三条边的三元组个数。

示例 1:
输入: [2,2,3,4]
输出: 3
解释:
有效的组合是:
2,3,4 (使用第一个 2)
2,3,4 (使用第二个 2)
2,2,3

注意:
		数组长度不超过1000。
		数组里整数的范围为 [0, 1000]。
*/

int triangleNumber(vector<int>& nums)
{
	sort(nums.begin(), nums.end());
	int sum = 0;
	int len = static_cast<int>(nums.size());
	for (--len; len >= 2; --len)
	{
		int L = 0, R = len - 1;
		while (L < R)
		{
			if (nums[L] + nums[R] > nums[len])
			{
				sum += R - L;
				--R;
			}
			else
				++L;
		}
	}
	return sum;
}


int main()
{
	vector<int> nums = { 2, 2, 3, 4 };
	OutExpr(triangleNumber(nums), "%d");
}
