#include "leetcode.hpp"

/* 587. 安装栅栏

在一个二维的花园中，有一些用 (x, y) 坐标表示的树。由于安装费用十分昂贵，你的任务是先用最短的绳子围起所有的树。只有当所有的树都被绳子包围时，花园才能围好栅栏。你需要找到正好位于栅栏边界上的树的坐标。

注意:
	所有的树应当被围在一起。你不能剪断绳子来包围树或者把树分成一组以上。
	输入的整数在 0 到 100 之间。
	花园至少有一棵树。
	所有树的坐标都是不同的。
	输入的点没有顺序。输出顺序也没有要求。

https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/erect_the_fence_1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/erect_the_fence_2.png
*/

// https://leetcode-cn.com/problems/erect-the-fence/solution/an-zhuang-zha-lan-by-leetcode/
// 凸包。没写过，直接抄的单调链算法

typedef vector<int> point;

int orientation(point const& p, point const& q, point const& r)
{
	return (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
}


vector<point> outerTrees(vector<point>& pts)
{
	int len = static_cast<int>(pts.size());
	vector<int> idxs;

	sort(pts.begin(), pts.end(),
		[](point const& p, point const& q) -> bool
	{
		return (p[0] < q[0]) || (p[0] == q[0] && p[1] < q[1]);
	});

	for (int i = 0; i < len; ++i)
	{
		for (size_t sz = idxs.size(); sz >= 2; --sz, idxs.pop_back())
		{
			if (orientation(pts[idxs[sz - 2]], pts[idxs[sz - 1]], pts[i]) <= 0)
				break;
		}
		idxs.push_back(i);
	}
	idxs.pop_back();
	for (int i = len - 1; i >= 0; --i)
	{
		for (size_t sz = idxs.size(); sz >= 2; --sz, idxs.pop_back())
		{
			if (orientation(pts[idxs[sz - 2]], pts[idxs[sz - 1]], pts[i]) <= 0)
				break;
		}
		idxs.push_back(i);
	}

	sort(idxs.begin(), idxs.end());
	len = static_cast<int>(
		unique(idxs.begin(), idxs.end()) - idxs.begin());
	vector<point> hull;
	hull.reserve(idxs.size());
	for (int i = 0; i < len; ++i)
		hull.push_back(pts[idxs[i]]);
	return hull;
}


int main()
{
	vector<vector<int>> points = {
		{ 1, 1 }, { 2, 2 }, { 2, 0 },
		{ 2, 4 }, { 3, 3 }, { 4, 2 }
	};
	output(outerTrees(points), "Erect the Fence");
}
