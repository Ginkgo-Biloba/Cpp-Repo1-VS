#include "leetcode.hpp"

/* 1453. 圆形靶内的最大飞镖数量

墙壁上挂着一个圆形的飞镖靶。
现在请你蒙着眼睛向靶上投掷飞镖。

投掷到墙上的飞镖用二维平面上的点坐标数组表示。
飞镖靶的半径为 r 。

请返回能够落在 任意 半径为 r 的圆形靶内或靶上的最大飞镖数。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/16/sample_1_1806.png
输入：points = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
输出：4
解释：如果圆形的飞镖靶的圆心为 (0,0) ，半径为 2 ，所有的飞镖都落在靶上，此时落在靶上的飞镖数最大，值为 4 。

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/16/sample_2_1806.png
输入：points = [[-3,0],[3,0],[2,6],[5,4],[0,9],[7,8]], r = 5
输出：5
解释：如果圆形的飞镖靶的圆心为 (0,4) ，半径为 5 ，则除了 (7,8) 之外的飞镖都落在靶上，此时落在靶上的飞镖数最大，值为 5 。

示例 3：
输入：points = [[-2,0],[2,0],[0,2],[0,-2]], r = 1
输出：1

示例 4：
输入：points = [[1,2],[3,5],[1,-1],[2,3],[4,1],[1,3]], r = 2
输出：4

提示：
1 <= points.length <= 100
points[i].length == 2
-10^4 <= points[i][0], points[i][1] <= 10^4
1 <= r <= 5000
*/


class Solution
{
	struct Point { int x, y, n; };

	int len, ans;
	double rsq;
	vector<Point> pts;

	void count(double x, double y)
	{
		int n = 0;
		for (int i = 0; i < len; ++i)
		{
			double ix = x - pts[i].x;
			double iy = y - pts[i].y;
			if (ix * ix + iy * iy <= rsq)
				n += pts[i].n;
		}
		ans = max(ans, n);
	}

public:
	int numPoints(vector<vector<int>>& points, int r)
	{
		ans = 0;
		pts.clear();
		rsq = r * r;
		// 去重
		sort(points.begin(), points.end());
		len = static_cast<int>(points.size());
		for (int i = 0; i < len;)
		{
			int x = points[i][0];
			int y = points[i][1];
			int k = i + 1;
			for (; k < len; ++k)
			{
				if ((x != points[k][0]) || (y != points[k][1]))
					break;
			}
			pts.push_back({ x, y, k - i });
			// 单个点的最大次数
			ans = max(ans, k - i);
			i = k;
		}
		len = static_cast<int>(pts.size());
		// 任意两点在圆边上，确定一个圆，统计圆内的点数
		for (int i = 0; i < len; ++i)
		{
			double x0 = pts[i].x;
			double y0 = pts[i].y;
			for (int k = i + 1; k < len; ++k)
			{
				double x1 = pts[k].x;
				double y1 = pts[k].y;
				double hx = (x0 - x1) * 0.5;
				double hy = (y0 - y1) * 0.5;
				// 两个点的距离的一半的平方 half dist
				double hd = hx * hx + hy * hy;
				if (hd > rsq)
					continue;
				double ox = (x0 + x1) * 0.5;
				double oy = (y0 + y1) * 0.5;
				// 垂直平分线上的偏移距离
				double vd = sqrt(rsq - hd);
				double rh = 1.0 / sqrt(hd);
				// 垂直平分线上的偏移向量的垂线
				double dx = vd * hx * rh;
				double dy = vd * hy * rh;
				// 分别往垂直平分线两边偏移
				count(ox + dy, oy - dx);
				count(ox - dy, oy + dx);
			}
		}
		return ans;
	}
};


int main()
{
	vector<vector<int>>
		a = { { -2, 0 }, { 2, 0 }, { 0, 2 }, { 0, -2 } },
		b = { { -3, 0 }, { 3, 0 }, { 2, 6 }, { 5, 4 }, { 0, 9 }, { 7, 8 } },
		c = { { -2, 0 }, { 2, 0 }, { 0, 2 }, { 0, -2 } },
		d = { { 1, 2 }, { 3, 5 }, { 1, -1 }, { 2, 3 }, { 4, 1 }, { 1, 3 } };
	Solution s;
	OutExpr(s.numPoints(a, 2), "%d");
	OutExpr(s.numPoints(b, 5), "%d");
	OutExpr(s.numPoints(c, 1), "%d");
	OutExpr(s.numPoints(d, 2), "%d");
}
