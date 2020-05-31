#include "leetcode.hpp"

/* 283. 移动零

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]

说明:
	必须在原数组上操作，不能拷贝额外的数组。
	尽量减少操作次数。
*/

void moveZeroes(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int h, i = 0;
	for (; i < len; ++i)
	{
		if (A[i] == 0)
			break;
	}
	h = i;
	for (++i; i < len; ++i)
		if (A[i] != 0)
		{
			A[h] = A[i];
			++h;
		}
	for (; h < len; ++h)
		A[h] = 0;
}


int main()
{}
