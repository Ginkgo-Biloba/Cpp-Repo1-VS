#include "leetcode.hpp"

/* 223. 矩形面积

在二维平面上计算出两个由直线构成的矩形重叠后形成的总面积。

每个矩形由其左下顶点和右上顶点坐标表示，如图所示。

https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rectangle_area.png
Rectangle Area

示例:

输入: -3, 0, 3, 4, 0, -1, 9, 2
输出: 45

说明: 假设矩形面积不会超出 int 的范围。
*/

int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
{
	int p = (C - A) * (D - B);
	int q = (G - E) * (H - F);
	A = max(A, E);
	B = max(B, F);
	C = max(A, min(C, G));
	D = max(B, min(D, H));
	return p - (C - A) * (D - B) + q;
}


int main()
{}
