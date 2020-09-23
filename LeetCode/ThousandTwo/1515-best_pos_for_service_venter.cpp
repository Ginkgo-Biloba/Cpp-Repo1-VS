#include "leetcode.hpp"

/* 1515. 服务中心的最佳位置

一家快递公司希望在新城市建立新的服务中心。
公司统计了该城市所有客户在二维地图上的坐标，并希望能够以此为依据为新的服务中心选址：使服务中心 到所有客户的欧几里得距离的总和最小 。

给你一个数组 positions ，其中 positions[i] = [xi, yi] 表示第 i 个客户在二维地图上的位置，返回到所有客户的 欧几里得距离的最小总和 。

换句话说，请你为服务中心选址，该位置的坐标 [xcentre, ycentre] 需要使下面的公式取到最小值：
https://assets.leetcode.com/uploads/2020/06/25/q4_edited.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/07/12/q4_edited.jpg

与真实值误差在 10^-5 之内的答案将被视作正确答案。

示例 1：
https://assets.leetcode.com/uploads/2020/06/25/q4_e1.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/07/12/q4_e1.jpg
输入：positions = [[0,1],[1,0],[1,2],[2,1]]
输出：4.00000
解释：如图所示，你可以选 [xcentre, ycentre] = [1, 1] 作为新中心的位置，这样一来到每个客户的距离就都是 1，所有距离之和为 4 ，这也是可以找到的最小值。

示例 2：
https://assets.leetcode.com/uploads/2020/06/25/q4_e3.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/07/12/q4_e3.jpg
输入：positions = [[1,1],[3,3]]
输出：2.82843
解释：欧几里得距离可能的最小总和为 sqrt(2) + sqrt(2) = 2.82843

示例 3：
输入：positions = [[1,1]]
输出：0.00000

示例 4：
输入：positions = [[1,1],[0,0],[2,0]]
输出：2.73205
解释：乍一看，你可能会将中心定在 [1, 0] 并期待能够得到最小总和，但是如果选址在 [1, 0] 距离总和为 3
如果将位置选在 [1.0, 0.5773502711] ，距离总和将会变为 2.73205
当心精度问题！

示例 5：
输入：positions = [[0,1],[3,2],[4,5],[7,6],[8,9],[11,1],[2,12]]
输出：32.94036
解释：你可以用 [4.3460852395, 4.9813795505] 作为新中心的位置

提示：
	1 <= positions.length <= 50
	positions[i].length == 2
	0 <= positions[i][0], positions[i][1] <= 100
*/


class Solution
{
	vector<vector<int>> pos;
	double alpha, beta, epsilon;

	double distance(double x, double y)
	{
		double s = 0;
		for (auto& p : pos)
			s += hypot(p[0] - x, p[1] - y);
		return s;
	}

	double ysearch(double y0, double y1, double x)
	{
		while (y1 - y0 > 1e-7)
		{
			double m0 = y0 + (y1 - y0) / 3.0;
			double m1 = y1 - (m0 - y0);
			double d0 = distance(x, m0);
			double d1 = distance(x, m1);
			if (d0 < d1)
				y1 = m1;
			else
				y0 = m0;
		}
		return distance(x, (y0 + y1) * 0.5);
	}

	array<double, 2> gradient(double x, double y)
	{
		array<double, 2> g = { 0, 0 };
		for (auto& p : pos)
		{
			double xp = x - p[0], yp = y - p[1];
			double dp = 1.0 / hypot(xp, yp);
			g[0] += (x - p[0]) * dp;
			g[1] += (y - p[1]) * dp;
		}
		return g;
	}

	double armijo(double x, double y, double eps)
	{
		array<double, 2> g = gradient(x, y);
		double d0 = distance(x, y);
		double d1 = distance(x - g[0] * eps, y - g[1] * eps);
		double dexpect = alpha * eps * (g[0] * g[0] + g[1] * g[1]);
		//printf("%f - %f , %f\n", d0, d1, dexpect);
		bool succeed = (d0 - d1 >= dexpect);
		return succeed;
	}

	double backtrack(double x, double y)
	{
		double eps = epsilon;
		while (eps > DBL_EPSILON && !armijo(x, y, eps))
			eps *= beta;
		return eps;
	}

public:
	// 抄的，三分查找
	double getMinDistSum3(vector<vector<int>>& positions)
	{
		// if (positions.size() < 2) return 0.0;
		pos.swap(positions);
		double x0 = 0, x1 = 100;
		double d0 = DBL_MAX, d1 = d0;
		// 对每一个 x，分别查找最优的 y
		while (x1 - x0 > 1e-7)
		{
			double m0 = x0 + (x1 - x0) / 3.0;
			double m1 = x1 - (m0 - x0);
			d0 = ysearch(0.0, 100.0, m0);
			d1 = ysearch(0.0, 100.0, m1);
			if (d0 < d1)
				x1 = m1;
			else
				x0 = m0;
		}
		pos.swap(positions);
		return min(d0, d1);
	}

	// https://leetcode.com/problems/best-position-for-a-service-centre/discuss/731547/Python-Gradient-Descent-with-Armijo-stepsize-rule
	// 抄的，梯度下降
	double getMinDistSum(vector<vector<int>>& positions)
	{
		pos.swap(positions);
		alpha = 0.5;
		beta = 0.8;
		epsilon = 1.0;
		double x = 0.1, y = 0.1;
		double d = distance(x, y);
		array<double, 2> g;
		int loop = 0;
		for (; loop < 1000; ++loop)
		{
			double step = backtrack(x, y);
			g = gradient(x, y);
			x -= step * g[0];
			y -= step * g[1];
			double d0 = d;
			d = distance(x, y);
			// printf("\td0 : %.14f, d : %.14f\n", d0, d);
			if (d0 - d < 1e-7)
				break;
		}
		printf("\tloop = %d\n", loop);
		pos.swap(positions);
		return d;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 0, 1 }, { 1, 0 }, { 1, 2 }, { 2, 1 } },
		b = { { 1, 1 }, { 3, 3 } },
		c = { { 1, 1 } },
		d = { { 1, 1 }, { 0, 0 }, { 2, 0 } },
		e = { { 0, 1 }, { 3, 2 }, { 4, 5 }, { 7, 6 }, { 8, 9 }, { 11, 1 }, { 2, 12 } },
		f = { { 27, 90 }, { 99, 75 }, { 99, 38 } },
		g = { { 44, 23 }, { 18, 45 }, { 6, 73 }, { 0, 76 }, { 10, 50 }, { 30, 7 }, { 92, 59 }, { 44, 59 }, { 79, 45 }, { 69, 37 }, { 66, 63 }, { 10, 78 }, { 88, 80 }, { 44, 87 } };
	Solution s;
	OutExpr(s.getMinDistSum(a), "%f");
	OutExpr(s.getMinDistSum(b), "%f");
	OutExpr(s.getMinDistSum(c), "%f");
	OutExpr(s.getMinDistSum(d), "%f");
	OutExpr(s.getMinDistSum(e), "%f");
	OutExpr(s.getMinDistSum(f), "%f"); // 109.30317
	OutExpr(s.getMinDistSum(g), "%f"); // 499.28078
}
