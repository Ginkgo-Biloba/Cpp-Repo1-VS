#include "leetcode.hpp"

/* 658. 找到 K 个最接近的元素

给定一个排序好的数组，两个整数 k 和 x，从数组中找到最靠近 x（两数之差最小）的 k 个数。
返回的结果必须要是按升序排好的。如果有两个数与 x 的差值一样，优先选择数值较小的那个数。

示例 1:
输入: [1,2,3,4,5], k=4, x=3
输出: [1,2,3,4]

示例 2:
输入: [1,2,3,4,5], k=4, x=-1
输出: [1,2,3,4]

说明:
	k 的值为正数，且总是小于给定排序数组的长度。
	数组不为空，且长度不超过 104
	数组里的每个元素与 x 的绝对值不超过 104

更新(2017/9/19):
这个参数 arr 已经被改变为一个整数数组（而不是整数列表）。
请重新加载代码定义以获取最新更改。
*/


vector<int> findClosestElements(vector<int>& ary, int k, int x)
{
	int len = static_cast<int>(ary.size());
	vector<int> nums;
	int R = static_cast<int>(
		std::upper_bound(ary.begin(), ary.end(), x)
		- ary.begin());
	R = std::min(std::max(R, 0), len);
	int L = R - 1;
	while (R - L < k + 1)
	{
		int d0 = INT_MAX, d1 = INT_MAX;
		if (L >= 0)
			d0 = std::abs(x - ary[L]);
		if (R < len)
			d1 = std::abs(x - ary[R]);
		if (d1 < d0)
			++R;
		else
			--L;
	}
	nums.reserve(k);
	for (++L; L < R; ++L)
		nums.push_back(ary[L]);
	return nums;
}


int main()
{
	vector<int> ary = { 1, 2, 3, 4, 5 };
	output(findClosestElements(ary, 4, 3), "Find K Closest Elements");
	output(findClosestElements(ary, 4, 4), "Find K Closest Elements");
}
