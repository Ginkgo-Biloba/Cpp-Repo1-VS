#include "leetcode.hpp"

/* 1551. 使数组中所有元素相等的最小操作数

存在一个长度为 n 的数组 arr ，其中 arr[i] = (2 * i) + 1 （ 0 <= i < n ）。

一次操作中，你可以选出两个下标，记作 x 和 y （ 0 <= x, y < n ）并使 arr[x] 减去 1 、arr[y] 加上 1 （即 arr[x] -=1 且 arr[y] += 1 ）。
最终的目标是使数组中的所有元素都 相等 。
题目测试用例将会 保证 ：在执行若干步操作后，数组中的所有元素最终可以全部相等。

给你一个整数 n，即数组的长度。
请你返回使数组 arr 中所有元素相等所需的 最小操作数 。

示例 1：
输入：n = 3
输出：2
解释：arr = [1, 3, 5]
第一次操作选出 x = 2 和 y = 0，使数组变为 [2, 3, 4]
第二次操作继续选出 x = 2 和 y = 0，数组将会变成 [3, 3, 3]

示例 2：
输入：n = 6
输出：9

提示：
	1 <= n <= 10^4
*/

int minOperations(int n)
{
	// int m = 0;
	// for (int i = 1; i < n; i += 2)
	// 	m += n - i;
	// return m;
	int a = !(n & 1); // 首项
	int m = (n + 1) / 2; // 项数
	int s = a * m + m * (m - 1) / 2 * 2;
	return s;
}


int main()
{
	OutExpr(minOperations(3), "%d");
	OutExpr(minOperations(6), "%d");
	OutExpr(minOperations(7), "%d");
}
