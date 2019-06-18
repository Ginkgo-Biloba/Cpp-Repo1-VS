#include "../srcOld/utility.hpp"

/* 390. 消除游戏

给定一个从 1 到 n 排序的整数列表。
首先，从左到右，从第一个数字开始，每隔一个数字进行删除，直到列表的末尾。
第二步，在剩下的数字中，从右到左，从倒数第一个数字开始，每隔一个数字进行删除，直到列表开头。
我们不断重复这两步，从左到右和从右到左交替进行，直到只剩下一个数字。
返回长度为 n 的列表中，最后剩下的数字。

示例：
输入:
n = 9,
1 2 3 4 5 6 7 8 9
2 4 6 8
2 6
6
输出：
6
*/

// https://leetcode.com/problems/elimination-game/discuss/87119/JAVA:-Easiest-solution-O(logN)-with-explanation
// 抄的
int lastRemaining(int n)
{
	bool left = true;
	int rest = n;
	int step = 1;
	int head = 1;
	while (rest > 1)
	{
		if (left || rest % 2 == 1)
			head += step;
		rest /= 2;
		step *= 2;
		left = !left;
	}

	return head;
}


int main()
{
	OutExpr(lastRemaining(24), "%d");
}
