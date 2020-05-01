#include "leetcode.hpp"

/* 1401. 圆和矩形是否有重叠

给你一个以 (radius, x_center, y_center) 表示的圆和一个与坐标轴平行的矩形 (x1, y1, x2, y2)，其中 (x1, y1) 是矩形左下角的坐标，(x2, y2) 是右上角的坐标。

如果圆和矩形有重叠的部分，请你返回 True ，否则返回 False 。

换句话说，请你检测是否 存在 点 (xi, yi) ，它既在圆上也在矩形上（两者都包括点落在边界上的情况）。

示例 1：
输入：radius = 1, x_center = 0, y_center = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
输出：true
解释：圆和矩形有公共点 (1,0)

示例 2：
输入：radius = 1, x_center = 0, y_center = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1
输出：true

示例 3：
输入：radius = 1, x_center = 1, y_center = 1, x1 = -3, y1 = -3, x2 = 3, y2 = 3
输出：true

示例 4：
输入：radius = 1, x_center = 1, y_center = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
输出：false

提示：
	1 <= radius <= 2000
	-10^4 <= x_center, y_center, x1, y1, x2, y2 <= 10^4
	x1 < x2
	y1 < y2
*/

class Solution
{
	double square(double x)
	{
		return x * x;
	}

public:
	bool checkOverlap_org(int radius, int x_center, int y_center,
		int x1, int y1, int x2, int y2)
	{
		/// 把长方形移动到中心
		double Rw = (x2 - x1) / 2.0; // 半宽
		double Rh = (y2 - y1) / 2.0; // 半高
		double Cx = x_center - (x2 + x1) * 0.5;
		double Cy = y_center - (y2 + y1) * 0.5;
		double Cr = radius;
		/// 镜像到第一象限
		Cx = fabs(Cx);
		Cy = fabs(Cy);
		/// 算区域
		bool s0 = (Cx <= Rw) && (Cy <= Rh + Cr); // 上面
		bool s1 = (Cx <= Rw + Cr) && (Cy <= Rh); // 右面
		bool s2 = square(Cx - Rw) + square(Cy - Rh) <= square(Cr); // 右上角
		return s0 || s1 || s2;
	}

	// https://www.zhihu.com/question/24251545/answer/123994977
	bool checkOverlap(int radius, int x_center, int y_center,
		int x1, int y1, int x2, int y2)
	{
		/// 把长方形移动到中心
		double Rw = (x2 - x1) / 2.0; // 半宽
		double Rh = (y2 - y1) / 2.0; // 半高
		double Rx = (x2 + x1) * 0.5;
		double Ry = (y2 + y1) * 0.5;
		double Dx = x_center - Rx;
		double Dy = y_center - Ry;
		double Cr = radius;
		Dx = min(max(Dx, -Rw), Rw);
		Dy = min(max(Dy, -Rh), Rh);
		Dx = Dx + Rx - x_center;
		Dy = Dy + Ry - y_center;
		return Dx * Dx + Dy * Dy <= Cr * Cr;
	}
};


int main()
{
	Solution s;
	OutBool(s.checkOverlap(1, 0, 0, 1, -1, 3, 1));
	OutBool(s.checkOverlap(1, 0, 0, -1, 0, 0, 1));
	OutBool(s.checkOverlap(1, 1, 1, -3, -3, 3, 3));
	OutBool(s.checkOverlap(1, 1, 1, 1, -3, 2, -1));
}
