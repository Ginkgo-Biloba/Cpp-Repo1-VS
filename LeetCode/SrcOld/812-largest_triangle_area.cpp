#include "leetcode.hpp"

/* 812. 最大三角形面积

给定包含多个点的集合，从其中取三个点组成三角形，返回能组成的最大三角形的面积。

示例:
输入: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
输出: 2
解释:
这五个点如下图所示。组成的橙色三角形是最大的，面积为2。

注意:
	3 <= points.length <= 50.
	不存在重复的点。
	-50 <= points[i][j] <= 50.
	结果误差值在 10^-6 以内都认为是正确答案。
*/

// https://leetcode.com/problems/largest-triangle-area/discuss/122711/C%2B%2BJavaPython-Solution-with-Explanation-and-Prove
// S_{ABC} = |\vec{AB} × \vec{AC}| / 2
double largestTriangleArea(vector<vector<int>>& points)
{
	double m = 0.0;
	int len = static_cast<int>(points.size());
	for (int i0 = 0; i0 < len - 2; ++i0)
	{
		double Ax = points[i0][0], Ay = points[i0][1];
		for (int i1 = i0 + 1; i1 < len - 1; ++i1)
		{
			double Bx = points[i1][0], By = points[i1][1];
			for (int i2 = i1 + 1; i2 < len; ++i2)
			{
				double Cx = points[i2][0], Cy = points[i2][1];
				double cur
					= Ax * By + Bx * Cy + Cx * Ay
					- Ax * Cy - Bx * Ay - Cx * By;
				m = std::max(m, std::fabs(cur));
			}
		}
	}
	return m * 0.5;
}


int main()
{
	vector<vector<int>>
		n0 = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 0, 2 }, { 2, 0 } };
	OutExpr(largestTriangleArea(n0), "%f");
}
