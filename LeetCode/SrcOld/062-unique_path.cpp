#include "leetcode.hpp"

/* 62. 不同路径

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。
机器人试图达到网格的右下角（在下图中标记为“Finish”）。

问总共有多少条不同的路径？

https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/robot_maze.png
例如，上图是一个7 x 3 的网格。有多少可能的路径？

示例 1:
输入: m = 3, n = 2
输出: 3
解释:
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向右 -> 向下
2. 向右 -> 向下 -> 向右
3. 向下 -> 向右 -> 向右

示例 2:
输入: m = 7, n = 3
输出: 28

提示：
	1 <= m, n <= 100
	题目数据保证答案小于等于 2 * 10 ^ 9
*/

int uniquePaths(int m, int n)
{
	--m;
	--n;
	// C(s, n) 或者 C(s, m) -> C(s, x)
	int s = m + n;
	int x = min(m, n);
	int64_t a = 1, b = 1;
	for (int i = 0; i < x; ++i)
	{
		a *= (s - i);
		b *= (i + 1);
	}
	return static_cast<int>(a / b);
}


int main()
{
	OutExpr(uniquePaths(3, 2), "%d");
	OutExpr(uniquePaths(7, 3), "%d");
}
