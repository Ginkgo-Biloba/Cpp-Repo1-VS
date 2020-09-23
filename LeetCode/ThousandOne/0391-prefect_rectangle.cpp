#include "leetcode.hpp"

/* 391. 完美矩形

我们有 N 个与坐标轴对齐的矩形, 其中 N > 0, 判断它们是否能精确地覆盖一个矩形区域。

每个矩形用左下角的点和右上角的点的坐标来表示。例如， 一个单位正方形可以表示为 [1,1,2,2]。 ( 左下角的点的坐标为 (1, 1) 以及右上角的点的坐标为 (2, 2) )。

示例 1:
rectangles =
[
	[1,1,3,3],
	[3,1,4,2],
	[3,2,4,4],
	[1,3,2,4],
	[2,3,3,4]
]
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rectangle_perfect.gif
返回 true。5个矩形一起可以精确地覆盖一个矩形区域。

示例 2:
rectangles =
[
	[1,1,2,3],
	[1,3,2,4],
	[3,1,4,2],
	[3,2,4,4]
]
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rectangle_separated.gif
返回 false。两个矩形之间有间隔，无法覆盖成一个矩形。

示例 3:
rectangles =
[
	[1,1,3,3],
	[3,1,4,2],
	[1,3,2,4],
	[3,2,4,4]
]
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rectangle_hole.gif
返回 false。图形顶端留有间隔，无法覆盖成一个矩形。

示例 4:
rectangles =
[
	[1,1,3,3],
	[3,1,4,2],
	[1,3,2,4],
	[2,2,4,4]
]
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rectangle_intersect.gif
返回 false。因为中间有相交区域，虽然形成了矩形，但不是精确覆盖。
*/

class Solution
{
	// 注意 int -> int64_t -> uint64_t
	uint64_t combine(unsigned x, unsigned y)
	{
		return (static_cast<uint64_t>(x) << 32) | static_cast<uint64_t>(y);
	}
public:

	bool isRectangleCover(vector<vector<int>>& rects)
	{
		int xmin = INT_MAX, xmax = INT_MIN;
		int ymin = INT_MAX, ymax = INT_MIN;
		uint64_t border[4];
		int64_t areas = 0;
		std::map<uint64_t, int> count;
		size_t len = rects.size();

		for (size_t i = 0; i < len; ++i)
		{
			int const* pt = rects[i].data();
			xmin = std::min(xmin, pt[0]);
			xmax = std::max(xmax, pt[2]);
			ymin = std::min(ymin, pt[1]);
			ymax = std::max(ymax, pt[3]);
			areas += static_cast<int64_t>(pt[2] - pt[0]) * (pt[3] - pt[1]);
			uint64_t id0 = combine(pt[0], pt[1]);
			uint64_t id1 = combine(pt[0], pt[3]);
			uint64_t id2 = combine(pt[2], pt[3]);
			uint64_t id3 = combine(pt[2], pt[1]);
			count[id0] += 1;
			count[id1] += 1;
			count[id2] += 1;
			count[id3] += 1;
		}

		if (areas != static_cast<int64_t>(ymax - ymin) * (xmax - xmin))
			return false;

		border[0] = combine(xmin, ymin);
		border[1] = combine(xmin, ymax);
		border[2] = combine(xmax, ymax);
		border[3] = combine(xmax, ymin);

		for (int i = 0; i < 4; ++i)
		{
			if (count[border[i]] != 1)
				return false;
			count.erase(border[i]);
		}
		for (auto it : count)
		{
			if (it.second != 4 && it.second != 2)
				return false;
		}
		return true;
	}
};


int main()
{
	vector<vector<int>>
		a = {
			{ 1, 1, 3, 3 },
			{ 3, 1, 4, 2 },
			{ 3, 2, 4, 4 },
			{ 1, 3, 2, 4 },
			{ 2, 3, 3, 4 }
	},
		b = {
			{ 1, 1, 2, 3 },
			{ 1, 3, 2, 4 },
			{ 3, 1, 4, 2 },
			{ 3, 2, 4, 4 },
	},
	c = {
		{ 1, 1, 3, 3 },
		{ 3, 1, 4, 2 },
		{ 1, 3, 2, 4 },
		{ 3, 2, 4, 4 },
	},
	d = {
		{ 1, 1, 3, 3 },
		{ 3, 1, 4, 2 },
		{ 1, 3, 2, 4 },
		{ 2, 2, 4, 4 },
	};
	Solution s;
	OutBool(s.isRectangleCover(a));
	OutBool(s.isRectangleCover(b));
	OutBool(s.isRectangleCover(c));
	OutBool(s.isRectangleCover(d));
}
