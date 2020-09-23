#include "leetcode.hpp"

/* 342. 4的幂

给定一个整数 (32 位有符号整数)，请编写一个函数来判断它是否是 4 的幂次方。

示例 1:
输入: 16
输出: true

示例 2:
输入: 5
输出: false

进阶：
你能不使用循环或者递归来完成本题吗？
*/

bool isPowerOfFour(int n)
{
	if ((n < 0) || (n & (n - 1)))
		return false;

	// 二进制中 1 的位置需要在偶数位置上
	return (n & 0x55555555) != 0;
}


int main()
{}
