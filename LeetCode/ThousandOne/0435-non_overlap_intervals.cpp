#include "leetcode.hpp"

/* 435. 无重叠区间
给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。
注意:
		可以认为区间的终点总是大于它的起点。
		区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。

示例 1:
输入: [ [1,2], [2,3], [3,4], [1,3] ]
输出: 1
解释: 移除 [1,3] 后，剩下的区间没有重叠。

示例 2:
输入: [ [1,2], [1,2], [1,2] ]
输出: 2
解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。

示例 3:
输入: [ [1,2], [2,3] ]
输出: 0
解释: 你不需要移除任何区间，因为它们已经是无重叠的了。
*/

// 抄的
int eraseOverlapIntervals(vector<vector<int>>& intervals)
{
	int len = static_cast<int>(intervals.size());
	int count = 0;
	if (len == 0)
		return 0;
	std::sort(intervals.begin(), intervals.end(),
		[](vector<int> const& x, vector<int> const& y)
	{
		return x[0] < y[0];
	});
	int right = intervals[0][1];
	for (int i = 1; i < len; ++i)
		if (intervals[i][0] < right)
		{
			++count;
			right = std::min(right, intervals[i][1]);
		}
		else
			right = intervals[i][1];
	return count;
}


int main()
{
	vector<vector<int>> intervals = {
		{ 1, 2 },
		{ 2, 3 },
		{ 3, 4 },
		{ 1, 3 },
	};
	OutExpr(eraseOverlapIntervals(intervals), "%d");
}
