#include "leetcode.hpp"

/* 493. 翻转对

给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。

你需要返回给定数组中的重要翻转对的数量。

示例 1:
输入: [1,3,2,3,1]
输出: 2

示例 2:
输入: [2,4,3,5,1]
输出: 3

注意:
		给定数组的长度不会超过50000。
		输入数组中的所有数字都在32位整数的表示范围内。
*/

// https://leetcode.com/problems/reverse-pairs/discuss/97268/General-principles-behind-problems-similar-to-%22Reverse-Pairs%22
// 抄的
class Solution
{
	int* ptr;
	int len;

	int rev(int L, int R)
	{
		if (L >= R)
			return 0;
		int M = L + (R - L) / 2;
		int ans = rev(L, M) + rev(M + 1, R);

		int i = L, j = M + 1, p = M + 1;
		while (i <= M)
		{
			while (p <= R
				&& ptr[i] > INT64_C(2) * ptr[p])
				++p;
			ans += p - M - 1;
			while (j <= R && ptr[i] >= ptr[j])
				++j;
			++i;
		}

		std::inplace_merge(ptr + L, ptr + M + 1, ptr + R + 1);
		return ans;
	}


public:
	int reversePairs(vector<int>& nums)
	{
		ptr = nums.data();
		len = static_cast<int>(nums.size());
		int ans = rev(0, len - 1);
		return ans;
	}
};


int main()
{
	vector<int> nums = { 2, 4, 3, 5, 1 };
	OutExpr(Solution().reversePairs(nums), "%d");
}
