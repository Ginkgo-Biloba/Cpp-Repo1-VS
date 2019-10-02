#include "leetcode.hpp"

/* 593. 有效的正方形

给定二维空间中四点的坐标，返回四点是否可以构造一个正方形。

一个点的坐标（x，y）由一个有两个整数的整数数组表示。

示例:

输入: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
输出: True

注意:
	所有输入整数都在 [-10000，10000] 范围内。
	一个有效的正方形有四个等长的正长和四个等角（90度角）。
	输入点没有顺序。
*/

typedef vector<int> point;

int64_t di2(point const& a, point const& b)
{
	int64_t x = a[0] - b[0], y = a[1] - b[1];
	return x * x + y * y;
}


bool validSquare(vector<int> const& p1, vector<int> const& p2,
	vector<int> const& p3, vector<int> const& p4)
{
	int64_t d[6];
	d[0] = di2(p1, p2);
	d[1] = di2(p1, p3);
	d[2] = di2(p1, p4);
	d[3] = di2(p2, p3);
	d[4] = di2(p2, p4);
	d[5] = di2(p3, p4);
	std::sort(d, d + 6);
	return (d[0] > 0)
		&& (d[0] == d[1] && d[0] == d[2] && d[0] == d[3])
		&& (d[4] == d[5])
		&& (d[0] == d[4] / 2);
}


int main()
{
	OutExpr(
		boolstr[validSquare({ 0, 0 }, { 1, 1 }, { 1, 0 }, { 0, 1 })],
		"%s");
}
