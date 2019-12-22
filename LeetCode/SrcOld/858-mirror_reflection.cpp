#include "leetcode.hpp"

/* 858. 镜面反射

有一个特殊的正方形房间，每面墙上都有一面镜子。除西南角以外，每个角落都放有一个接受器，编号为 0， 1，以及 2。

正方形房间的墙壁长度为 p，一束激光从西南角射出，首先会与东墙相遇，入射点到接收器 0 的距离为 q。

返回光线最先遇到的接收器的编号（保证光线最终会遇到一个接收器）。

示例：
输入： p = 2, q = 1
输出： 2
解释： 这条光线在第一次被反射回左边的墙时就遇到了接收器 2 。
https://s3-lc-upload.s3.amazonaws.com/uploads/2018/06/18/reflection.png

提示：
	1 <= p <= 1000
	0 <= q <= p
*/

// https://leetcode-cn.com/problems/mirror-reflection/solution/jing-mian-fan-she-by-leetcode/
// 抄的
int gcd(int a, int b)
{
	int t = a % b;
	while (t)
	{
		a = b;
		b = t;
		t = a % b;
	}
	return b;
}

int mirrorReflection(int p, int q)
{
	int g = gcd(p, q);
	p /= g;
	p %= 2;
	q /= g;
	q %= 2;
	if (p == 1 && q == 1)
		return 1;
	return p == 1 ? 0 : 2;
}

int main()
{
	OutExpr(mirrorReflection(2, 1), "%d");
}
