#include "leetcode.hpp"

/* 1224. 最大相等频率

给出一个正整数数组 nums，请你帮忙从该数组中找出能满足下面要求的 最长 前缀，并返回其长度：
	从前缀中 删除一个 元素后，使得所剩下的每个数字的出现次数相同。

如果删除这个元素后没有剩余元素存在，仍可认为每个数字都具有相同的出现次数（也就是 0 次）。

示例 1：
输入：nums = [2,2,1,1,5,3,3,5]
输出：7
解释：对于长度为 7 的子数组 [2,2,1,1,5,3,3]，如果我们从中删去 nums[4]=5，就可以得到 [2,2,1,1,3,3]，里面每个数字都出现了两次。

示例 2：
输入：nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
输出：13

示例 3：
输入：nums = [1,1,1,2,2,2]
输出：5

示例 4：
输入：nums = [10,2,8,9,3,8,1,5,2,3,7,6]
输出：8

提示：
	2 <= nums.length <= 10^5
	1 <= nums[i] <= 10^5
*/

// https://leetcode.com/problems/maximum-equal-frequency/discuss/403743/JavaC%2B%2BPython-Only-2-Cases%3A-Delete-it-or-not
// 抄的
class Solution
{
public:
	int maxEqualFreq(vector<int>& nums)
	{
		vector<int> count(100001), freq(100001);
		int len = static_cast<int>(nums.size());
		int ans = 0, a, c, d;
		for (int i = 1; i <= len; ++i)
		{
			a = nums[i - 1];
			++(count[a]);
			c = count[a];
			// 旧的出现次数减去 1
			--(freq[c - 1]);
			// 新的出现次数加上 1
			++(freq[c]);

			// 要 a
			// 所有元素都出现了 c 次
			// +1 是因为题目要求需要删除一个之后次数相等
			if ((freq[c] * c) == i && (i < len))
				ans = i + 1;
			d = i - freq[c] * c;
			// 不要 a
			// 当前数字出现了 1 次
			// 前面的都是同一个数字出现 i - 1 次
			if (((d == c + 1) || (d == 1)) && (freq[d] == 1))
				ans = i;
		}
		return ans;
	}
};


int main()
{
	vector<int>
		a = { 2, 2, 1, 1, 5, 3, 3, 5 },
		b = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5 },
		c = { 1, 1, 1, 2, 2, 2 },
		d = { 10, 2, 8, 9, 3, 8, 1, 5, 2, 3, 7, 6 },
		e = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Solution s;
	OutExpr(s.maxEqualFreq(a), "%d");
	OutExpr(s.maxEqualFreq(b), "%d");
	OutExpr(s.maxEqualFreq(c), "%d");
	OutExpr(s.maxEqualFreq(d), "%d");
	OutExpr(s.maxEqualFreq(e), "%d");
}
