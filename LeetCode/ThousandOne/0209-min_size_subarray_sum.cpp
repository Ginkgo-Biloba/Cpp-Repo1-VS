#include "leetcode.hpp"

/* 209. 长度最小的子数组

给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。
如果不存在符合条件的连续子数组，返回 0。

示例:

输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。

进阶:
如果你已经完成了O(n) 时间复杂度的解法, 请尝试 O(n log n) 时间复杂度的解法。
*/

int minSubArrayLen(int s, vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int h = 0, i = 0, ans = len + 1;
	for (; i < len; ++i)
	{
		s -= A[i];
		if (s <= 0)
		{
			for (; s <= 0; ++h)
				s += A[h];
			ans = min(ans, i - h + 2);
		}
	}
	return ans > len ? 0 : ans;
}


int main()
{
	vector<int> a = { 2, 3, 9, 2, 4, 3 };
	OutExpr(minSubArrayLen(7, a), "%d");
}
