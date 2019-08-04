#include "leetcode.hpp"

/* 给定一位研究者论文被引用次数的数组（被引用次数是非负整数）
 * 编写一个方法，计算出研究者的 h 指数
 * h 指数的定义:
 *  - h 代表“高引用次数”（high citations）
 *  - 一名科研人员的 h 指数是指他（她）的 （N 篇论文中）至多有 h 篇论文分别被引用了至少 h 次
 *  - 其余的 N - h 篇论文每篇被引用次数不多于 h 次。
 */
int hIndex(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	std::sort(nums.begin(), nums.end(), std::greater<int>());

	// 这里如果使用二分查找就是下一道题，除了大小方向反一下
	int i = len;
	for (; i > 0; --i)
	{
		if (nums[i - 1] >= i)
			break;
	}

	return i;
}


int main()
{
	vector<int> nums = { 3, 0, 6, 1, 5 };
	int n = hIndex(nums);
	printf("hIndex: %d\n", n);
}
