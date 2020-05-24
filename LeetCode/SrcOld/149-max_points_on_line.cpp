#include "leetcode.hpp"

/* 149. 直线上最多的点数

给定一个二维平面，平面上有 n 个点，求最多有多少个点在同一条直线上。

示例 1:
输入: [[1,1],[2,2],[3,3]]
输出: 3
解释:
^
|
|        o
|     o
|  o
+------------->
0  1  2  3  4

示例 2:
输入: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
输出: 4
解释:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
*/

// https://leetcode.com/problems/max-points-on-a-line/discuss/47101/7-line-C++-concise-solution-NO-double-hash-key-or-GCD-for-slope/148722
// 抄的
class Solution
{
	struct Point { int x, y; };

	struct slope
	{
		bool operator()(Point const& a, Point const& b) const
		{
			int64_t d = (int64_t)(a.x) * b.y - (int64_t)(a.y) * (b.x);
			return ((int64_t)(a.y) * b.y > 0) ? (d > 0) : (d < 0);
		}
	};

public:
	int maxPoints(vector<vector<int>>& points)
	{
		int ans = 0;
		int len = static_cast<int>(points.size());
		for (int i = 0; i < len; ++i)
		{
			// points 没有排序，如果 k 从 i 开始，cur 需要在外面
			// 因为重复的点 a 可能会在组成直线的其他点 b 后面
			int dup = 0, cur = 0;
			map<Point, int, slope> m;
			Point a = { points[i][0], points[i][1] };
			for (int k = i; k < len; ++k)
			{
				Point b = { points[k][0], points[k][1] };
				if (a.x == b.x && a.y == b.y)
					++dup;
				else
				{
					b.x -= a.x;
					b.y -= a.y;
					cur = max(cur, ++m[b]);
				}
				ans = max(ans, cur + dup);
			}
		}
		return ans;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 1, 1 }, { 2, 2 }, { 3, 3 } },
		b = { { 1, 1 }, { 3, 2 }, { 5, 3 }, { 4, 1 }, { 2, 3 }, { 1, 4 } },
		c = { { 0, 0 }, { 1, 1 }, { 0, 0 } };
	Solution s;
	OutExpr(s.maxPoints(a), "%d");
	OutExpr(s.maxPoints(b), "%d");
	OutExpr(s.maxPoints(c), "%d");
}
