#include "leetcode.hpp"

/* 818. 赛车

你的赛车起始停留在位置 0，速度为 +1，正行驶在一个无限长的数轴上。
车也可以向负数方向行驶。

你的车会根据一系列由 A（加速）和 R（倒车）组成的指令进行自动驾驶 。

当车得到指令 "A" 时, 将会做出以下操作： position += speed, speed *= 2。

当车得到指令 "R" 时, 将会做出以下操作：
	如果当前速度是正数，则将车速调整为 speed = -1；
	否则将车速调整为 speed = 1。当前所处位置不变。

例如，当得到一系列指令 "AAR" 后, 你的车将会走过位置 0->1->3->3，并且速度变化为 1->2->4->-1。

现在给定一个目标位置，请给出能够到达目标位置的最短指令列表的长度。

示例 1:
输入:
target = 3
输出: 2
解释:
最短指令列表为 "AA"
位置变化为 0->1->3

示例 2:
输入:
target = 6
输出: 5
解释:
最短指令列表为 "AAARA"
位置变化为 0->1->3->7->7->6

说明:
	1 <= target（目标位置） <= 10000。
*/

uint64_t make(int x, int y)
{
	// 注意 int -> int64_t -> uint64_t 
	// 不是 int -> unsigned -> uint64_t
	unsigned ux = x, uy = y;
	return (static_cast<uint64_t>(ux) << 32) | (uy);
}

void split(uint64_t v, int& x, int& y)
{
	x = static_cast<int>(v >> 32);
	y = static_cast<int>(v & UINT_MAX);
}

int racecar(int target)
{
	// 没看懂，对称性？
	unsigned const tmax = target * 2;
	int step = 0;
	int x = 0, s = 1, len, x1, s1;
	uint64_t key = make(x, s);
	vector<uint64_t> prev, curr;
	unordered_set<uint64_t> visit;
	curr.push_back(key);
	visit.insert(key);

	while (!curr.empty())
	{
		++step;
		prev.swap(curr);
		curr.clear();
		len = static_cast<int>(prev.size());
		for (int i = 0; i < len; ++i)
		{
			split(prev[i], x, s);
			x1 = x + s;
			s1 = s * 2;
			key = make(x1, s1);
			if (x1 == target)
				return step;
			if ((static_cast<unsigned>(x1) < tmax)
				&& (visit.find(key) == visit.end()))
			{
				curr.push_back(key);
				visit.insert(key);
			}
			x1 = x;
			s1 = s > 0 ? -1 : 1;
			key = make(x1, s1);
			if ((static_cast<unsigned>(x1) < tmax)
				&& (visit.find(key) == visit.end()))
			{
				curr.push_back(key);
				visit.insert(key);
			}
		}
	}

	/*for (uint64_t k : visit)
	{
		split(k, x, s);
		printf("%3d  %3d\n", x, s);
	}*/

	return -1;
}


int main()
{
	OutExpr(racecar(3), "%d");
	OutExpr(racecar(5), "%d");
	OutExpr(racecar(6), "%d");
}
