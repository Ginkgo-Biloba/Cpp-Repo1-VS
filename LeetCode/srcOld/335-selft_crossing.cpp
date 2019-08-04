#include "leetcode.hpp"

/* 335. 路径交叉

给定一个含有 n 个正数的数组 x。
从点 (0,0) 开始，先向北移动 x[0] 米，然后向西移动 x[1] 米，向南移动 x[2] 米，向东移动 x[3] 米，持续移动。
也就是说，每次移动后你的方位会发生逆时针变化。
编写一个 O(1) 空间复杂度的一趟扫描算法，判断你所经过的路径是否相交。

示例 1:

┌───┐
│　　　│
└───┼──>
　　　　│

输入: [2,1,1,2]
输出: true

示例 2:

┌──────┐
│　　　　　　│
│
│
└────────────>

输入: [1,2,3,4]
输出: false

示例 3:

┌───┐
│　　　│
└───┼>

输入: [1,1,1,1]
输出: true
*/

// https://leetcode.com/problems/self-crossing/discuss/79140/Re-post%3A-2-O(N)-C%2B%2B-0ms-solutions
// 抄的
bool isSelfCrossing(vector<int>& x)
{
	int i, len = static_cast<int>(x.size());
	if (len <= 3)
		return false;
	bool grow = x[2] > x[0];

	for (i = 3; i < len; ++i)
	{
		//if it is a "shrink" case before x[i] and cross happens
		if (!grow && x[i] >= x[i - 2])
			return true;
		// if it is a grow case, and x[i] changes it to shrink
		if (grow && x[i] <= x[i - 2])
		{
			grow = false;
			if (x[i] == x[i - 2] || (i > 3 && x[i - 2] - x[i - 4] <= x[i]))
				x[i - 1] -= x[i - 3];
		}
	}
	return false;
}

int main()
{
	vector<int> nums = { 2, 1, 1, 2 };
	bool n = isSelfCrossing(nums);
	printf("isSelfCrossing: %s\n", boolstr[n]);
}
