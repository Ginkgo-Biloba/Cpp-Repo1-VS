#include "leetcode.hpp"

/* 218. 天际线问题

城市的天际线是从远处观看该城市中所有建筑物形成的轮廓的外部轮廓。现在，假设您获得了城市风光照片（图A）上显示的所有建筑物的位置和高度，请编写一个程序以输出由这些建筑物形成的天际线（图B）。

https://leetcode-cn.com/static/images/problemset/skyline1.jpg
https://leetcode-cn.com/static/images/problemset/skyline2.jpg

https://leetcode.com/static/images/problemset/skyline1.jpg
https://assets.leetcode.com/uploads/2018/10/22/skyline2.png

每个建筑物的几何信息用三元组 [Li，Ri，Hi] 表示，其中 Li 和 Ri 分别是第 i 座建筑物左右边缘的 x 坐标，Hi 是其高度。可以保证 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX 和 Ri - Li > 0。您可以假设所有建筑物都是在绝对平坦且高度为 0 的表面上的完美矩形。

例如，图A中所有建筑物的尺寸记录为：[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] 。

输出是以 [ [x1,y1], [x2, y2], [x3, y3], ... ] 格式的“关键点”（图B中的红点）的列表，它们唯一地定义了天际线。关键点是水平线段的左端点。请注意，最右侧建筑物的最后一个关键点仅用于标记天际线的终点，并始终为零高度。此外，任何两个相邻建筑物之间的地面都应被视为天际线轮廓的一部分。

例如，图B中的天际线应该表示为：[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]。

说明:
	任何输入列表中的建筑物数量保证在 [0, 10000] 范围内。
	输入列表已经按左 x 坐标 Li  进行升序排列。
	输出列表必须按 x 位排序。
	输出天际线中不得有连续的相同高度的水平线。例如 [...[2 3], [4 5], [7 5], [11 5], [12 7]...] 是不正确的答案；三条高度为 5 的线应该在最终输出中合并为一个：[...[2 3], [4 5], [12 7], ...]
*/

// https://leetcode.com/problems/the-skyline-problem/discuss/61279/My-C%2B%2B-code-using-one-priority-queue-(812-ms)
// 抄的
vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
{
	// 高度，右边界
	priority_queue<pair<int, int>> livebd;
	vector<vector<int>> res;
	int idx = 0, curX, curH = -1;
	int len = static_cast<int>(buildings.size());
	// 如果新的建筑没有处理，或者待处理的建筑不为空
	while (idx < len || !livebd.empty())
	{
		// 下一个要考虑的关键点
		curX = livebd.empty() ? buildings[idx][0] : livebd.top().second;

		// 检查当前最高的建筑是否在下一个关键点之前结束
		if (idx >= len || buildings[idx][0] > curX)
		{
			// 弹出处理过的建筑，即那些高度比当前小的，并且在当前建筑右边界之前的
			while (!livebd.empty() && (livebd.top().second <= curX))
				livebd.pop();
		}
		// 如果新的建筑在最高的建筑右边界之前开始，则添加新的建筑
		else
		{
			curX = buildings[idx][0];
			// 直接添加所有左边界相同的新建筑
			while (idx < len && buildings[idx][0] == curX)
			{
				livebd.emplace(buildings[idx][2], buildings[idx][1]);
				++idx;
			}
		}
		curH = livebd.empty() ? 0 : livebd.top().first;
		if (res.empty() || (res.back()[1] != curH))
			res.push_back({ curX, curH });
	}
	return res;
}


int main()
{
	vector<vector<int>>
		a = { { 2, 9, 10 }, { 3, 7, 15 }, { 5, 12, 12 }, { 15, 20, 10 }, { 19, 24, 8 } };
	output(getSkyline(a), "Skyline");
}
