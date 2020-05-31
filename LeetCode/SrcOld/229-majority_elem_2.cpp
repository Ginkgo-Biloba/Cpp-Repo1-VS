#include "leetcode.hpp"

/* 229. 求众数 II

给定一个大小为 n 的数组，找出其中所有出现超过 ⌊ n/3 ⌋ 次的元素。

说明: 要求算法的时间复杂度为 O(n)，空间复杂度为 O(1)。

示例 1:

输入: [3,2,3]
输出: [3]

示例 2:

输入: [1,1,1,3,3,2,2,2]
输出: [1,2]
*/

// https://leetcode.com/problems/majority-element-ii/discuss/63520/Boyer-Moore-Majority-Vote-algorithm-and-my-elaboration
// 抄的
vector<int> majorityElement(vector<int>& nums)
{
	int len = static_cast<int>(nums.size());
	int a = 0, b = 1, p = 0, q = 0;
	for (int n : nums)
	{
		if (n == a)
			++p;
		else if (n == b)
			++q;
		else if (p == 0)
		{
			a = n;
			p = 1;
		}
		else if (q == 0)
		{
			b = n;
			q = 1;
		}
		else
		{
			--p;
			--q;
		}
	}
	p = q = 0;
	for (int n : nums)
	{
		p += (n == a);
		q += (n == b);
	}
	vector<int> R;
	if (p > len / 3)
		R.push_back(a);
	if (q > len / 3)
		R.push_back(b);
	return R;
}


int main()
{
	vector<int>
		a = { 3, 2, 3 },
		b = { 1, 1, 1, 3, 3, 2, 2, 2 };
	output(majorityElement(a), "Majority Element II");
	output(majorityElement(b), "Majority Element II");
}
