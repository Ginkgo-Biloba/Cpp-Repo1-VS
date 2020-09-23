#include "leetcode.hpp"

/* 96. 不同的二叉搜索树

给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？

示例:
输入: 3
输出: 5
解释:
给定 n = 3, 一共有 5 种不同结构的二叉搜索树:

>   1         3     3      2      1
>    \       /     /      / \      \
>     3     2     1      1   3      2
>    /     /       \                 \
>   2     1         2                 3
*/

// 卡特兰数
int numTrees(int n)
{
	vector<int> c(n + 2);
	c[0] = c[1] = 1;
	for (int i = 1; i < n; ++i)
	{
		for (int h = 0; h <= i; ++h)
			c[i + 1] += c[h] * c[i - h];
	}
	return c[n];
}


int main()
{
	for (int i = 0; i < 24;)
	{
		printf("%2d : %-9d    ", i, numTrees(i));
		if ((++i) % 4 == 0)
			puts("");
	}
}
