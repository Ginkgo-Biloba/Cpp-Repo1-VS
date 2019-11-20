#include "leetcode.hpp"

/* 693. 交替位二进制数

给定一个正整数，检查他是否为交替位二进制数：换句话说，就是他的二进制数相邻的两个位数永不相等。

示例 1:
输入: 5
输出: True
解释:
5的二进制数是: 101

示例 2:
输入: 7
输出: False
解释:
7的二进制数是: 111

示例 3:
输入: 11
输出: False
解释:
11的二进制数是: 1011

示例 4:
输入: 10
输出: True
解释:
10的二进制数是: 1010
*/

// https://leetcode.com/problems/binary-number-with-alternating-bits/discuss/108427/Oneliners-(C%2B%2B-Java-Ruby-Python)
// 抄的
bool hasAlternatingBits(int n)
{
	n ^= (n >> 2);
	return !(n & (n - 1));
}


int main()
{
	OutExpr(boolstr[hasAlternatingBits(5)], "%s");
	OutExpr(boolstr[hasAlternatingBits(7)], "%s");
	OutExpr(boolstr[hasAlternatingBits(10)], "%s");
	OutExpr(boolstr[hasAlternatingBits(11)], "%s");
	OutExpr(boolstr[hasAlternatingBits(13)], "%s");
}
