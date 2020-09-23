#include "leetcode.hpp"

/* 963. 最小面积矩形 II

给定在 xy 平面上的一组点，确定由这些点组成的任何矩形的最小面积，其中矩形的边不一定平行于 x 轴和 y 轴。

如果没有任何矩形，就返回 0。

示例 1：
输入：[[1,2],[2,1],[1,0],[0,1]]
输出：2.00000
解释：最小面积的矩形出现在 [1,2],[2,1],[1,0],[0,1] 处，面积为 2。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/22/1a.png

示例 2：
输入：[[0,1],[2,1],[1,1],[1,0],[2,0]]
输出：1.00000
解释：最小面积的矩形出现在 [1,0],[1,1],[2,1],[2,0] 处，面积为 1。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/23/2.png

示例 3：
输入：[[0,3],[1,2],[3,1],[1,3],[2,1]]
输出：0
解释：没法从这些点中组成任何矩形。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/23/3.png

示例 4：
输入：[[3,1],[1,1],[0,1],[2,1],[3,3],[3,2],[0,2],[2,3]]
输出：2.00000
解释：最小面积的矩形出现在 [2,1],[2,3],[3,3],[3,1] 处，面积为 2。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/21/4c.png

提示：
	1 <= points.length <= 50
	0 <= points[i][0] <= 40000
	0 <= points[i][1] <= 40000
	所有的点都是不同的。
	与真实值误差不超过 10^-5 的答案将视为正确结果。
*/

class Solution
{
	typedef std::complex<double> complexd;

	struct HashCD
	{
		std::hash<double> hd;

		size_t operator()(complexd const& a) const
		{
			return (~(hd(a.real()))) ^ (hd(a.imag()));
		}
	};

public:
	// https://leetcode.com/problems/minimum-area-rectangle-ii/discuss/208351/Python-Complex
	// 抄的
	double minAreaFreeRect(vector<vector<int>>& points)
	{
		int len = static_cast<int>(points.size());
		// 这里面的复数当向量用
		// 对于两个点组成的线段，键表示方向和长度，值表示线段中点
		unordered_map<complexd, vector<complexd>, HashCD> edges;
		vector<complexd> cpx;
		double ans = DBL_MAX;

		// sort 以防止出现 (-1,-1) 这种情况，它和 (1,1) 应该等价
		sort(points.begin(), points.end());
		cpx.reserve(len);
		for (int i = 0; i < len; ++i)
			cpx.emplace_back(points[i][0], points[i][1]);
		for (int i = 0; i < len; ++i)
			for (int k = i + 1; k < len; ++k)
			{
				complexd p = cpx[i], q = cpx[k];
				edges[q - p].push_back((q + p) * 0.5);
			}

		for (auto const& it : edges)
		{
			complexd a = it.first; // 方向和长度
			double absa = std::abs(a);
			len = static_cast<int>(it.second.size());
			for (int i = 0; i < len; ++i)
				for (int k = i + 1; k < len; ++k)
				{
					complexd p = it.second[i] - it.second[k];
					// 如果两条平行线段，长度相等，并且中点的连线与线段垂直
					// 那么它们就可以作为一个矩形的对边
					if (fabs(a.real() * p.real() + a.imag() * p.imag()) <= DBL_EPSILON)
						ans = min(ans, absa * std::abs(p));
				}
		}

		return ans == DBL_MAX ? 0.0 : ans;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 1, 2 }, { 2, 1 }, { 1, 0 }, { 0, 1 } },
		b = { { 0, 1 }, { 2, 1 }, { 1, 1 }, { 1, 0 }, { 2, 0 } },
		c = { { 0, 3 }, { 1, 2 }, { 3, 1 }, { 1, 3 }, { 2, 1 } },
		d = { { 3, 1 }, { 1, 1 }, { 0, 1 }, { 2, 1 }, { 3, 3 }, { 3, 2 }, { 0, 2 }, { 2, 3 } };
	Solution s;
	OutExpr(s.minAreaFreeRect(a), "%f");
	OutExpr(s.minAreaFreeRect(b), "%f");
	OutExpr(s.minAreaFreeRect(c), "%f");
	OutExpr(s.minAreaFreeRect(d), "%f");
}
