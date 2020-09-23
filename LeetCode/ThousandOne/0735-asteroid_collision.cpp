#include "leetcode.hpp"

/* 735. 行星碰撞

给定一个整数数组 asteroids，表示在同一行的行星。

对于数组中的每一个元素，其绝对值表示行星的大小，正负表示行星的移动方向（正表示向右移动，负表示向左移动）。
每一颗行星以相同的速度移动。

找出碰撞后剩下的所有行星。
碰撞规则：
	两个行星相互碰撞，较小的行星会爆炸。
	如果两颗行星大小相同，则两颗行星都会爆炸。
	两颗移动方向相同的行星，永远不会发生碰撞。

示例 1:
输入:
asteroids = [5, 10, -5]
输出: [5, 10]
解释:
10 和 -5 碰撞后只剩下 10。 5 和 10 永远不会发生碰撞。

示例 2:
输入:
asteroids = [8, -8]
输出: []
解释:
8 和 -8 碰撞后，两者都发生爆炸。

示例 3:
输入:
asteroids = [10, 2, -5]
输出: [10]
解释:
2 和 -5 发生碰撞后剩下 -5。10 和 -5 发生碰撞后剩下 10。

示例 4:
输入:
asteroids = [-2, -1, 1, 2]
输出: [-2, -1, 1, 2]
解释:
-2 和 -1 向左移动，而 1 和 2 向右移动。
由于移动方向相同的行星不会发生碰撞，所以最终没有行星发生碰撞。

说明:
	数组 asteroids 的长度不超过 10000。
	每一颗行星的大小都是非零整数，范围是 [-1000, 1000]。
*/

vector<int> asteroidCollision(vector<int>& ast)
{
	vector<int> stk;
	stk.reserve(ast.size());
	for (int cur : ast)
	{
		bool live = true;
		while (live && !stk.empty())
		{
			int pre = stk.back();
			// 同方向
			if (((pre ^ cur) >= 0) || (pre < 0))
				break;
			// pre 向右 cur 向左
			if (abs(pre) <= abs(cur))
				stk.pop_back();
			if (abs(pre) >= abs(cur))
			{
				live = false;
				break;
			}
		}
		if (live)
			stk.push_back(cur);
	}
	return stk;
}


int main()
{
	vector<int>
		a1 = { 5, 10, -5 },
		a2 = { 8, -8 },
		a3 = { 10, 2, -5 },
		a4 = { -2, -1, 1, 2 };
	output(asteroidCollision(a1), "a1");
	output(asteroidCollision(a2), "a2");
	output(asteroidCollision(a3), "a3");
	output(asteroidCollision(a4), "a4");
}
