#include "leetcode.hpp"

/* 1497. 检查数组对是否可以被 k 整除

给你一个整数数组 arr 和一个整数 k ，其中数组长度是偶数，值为 n 。

现在需要把数组恰好分成 n / 2 对，以使每对数字的和都能够被 k 整除。

如果存在这样的分法，请返回 True ；否则，返回 False 。

示例 1：
输入：arr = [1,2,3,4,5,10,6,7,8,9], k = 5
输出：true
解释：划分后的数字对为 (1,9),(2,8),(3,7),(4,6) 以及 (5,10) 。

示例 2：
输入：arr = [1,2,3,4,5,6], k = 7
输出：true
解释：划分后的数字对为 (1,6),(2,5) 以及 (3,4) 。

示例 3：
输入：arr = [1,2,3,4,5,6], k = 10
输出：false
解释：无法在将数组中的数字分为三对的同时满足每对数字和能够被 10 整除的条件。

示例 4：
输入：arr = [-10,10], k = 2
输出：true

示例 5：
输入：arr = [-1,1,-2,2,-3,3,-4,4], k = 3
输出：true

提示：
	arr.length == n
	1 <= n <= 10^5
	n 为偶数
	-10^9 <= arr[i] <= 10^9
	1 <= k <= 10^5
*/

bool canArrange(vector<int>& A, int k)
{
	vector<int> rem(k);
	for (int a : A)
		++(rem[(a % k + k) % k]);
	if (rem[0] & 1)
		return false;
	for (int i = 1; i <= k / 2; ++i)
	{
		if (rem[i] != rem[k - i])
			return false;
	}
	return true;
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 4, 5, 10, 6, 7, 8, 9 },
		b = { 1, 2, 3, 4, 5, 6 },
		c = { 1, 2, 3, 4, 5, 6 },
		d = { -10, 10 },
		e = { -1, 1, -2, 2, -3, 3, -4, 4 };
	OutBool(canArrange(a, 5));
	OutBool(canArrange(b, 7));
	OutBool(canArrange(c, 10));
	OutBool(canArrange(d, 2));
	OutBool(canArrange(e, 3));
}
