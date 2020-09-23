#include "leetcode.hpp"

/* 9. 回文数

判断一个整数是否是回文数。
回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

示例 1:
输入: 121
输出: true

示例 2:
输入: -121
输出: false
解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。

示例 3:
输入: 10
输出: false
解释: 从右向左读, 为 01 。因此它不是一个回文数。

进阶:
你能不将整数转为字符串来解决这个问题吗？
*/

bool isPalindrome(int x)
{
	int d = 10;
	if (x < 0)
		return false;
	if (x < 10)
		return true;
	while (x / d >= 10)
		d *= 10;
	while (d >= 10)
	{
		int a = x / d;
		int b = x % 10;
		if (a != b)
			return false;
		x = (x - a * d) / 10;
		d /= 100;
	}
	return true;
}

int main()
{
	OutBool(isPalindrome(9999));
	OutBool(isPalindrome(121));
	OutBool(isPalindrome(-121));
	OutBool(isPalindrome(10));
	OutBool(isPalindrome(11));
}
