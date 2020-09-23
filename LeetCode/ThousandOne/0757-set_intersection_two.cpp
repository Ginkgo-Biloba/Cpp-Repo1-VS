#include "leetcode.hpp"

/* 757. 设置交集大小至少为2

一个整数区间 [a, b] ( a < b ) 代表着从 a 到 b 的所有连续整数，包括 a 和 b。

给你一组整数区间 intervals，请找到一个最小的集合 S，使得 S 里的元素与区间 intervals 中的每一个整数区间都至少有2个元素相交。

输出这个最小集合S的大小。

示例 1:
输入: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
输出: 3
解释:
考虑集合 S = {2, 3, 4}. S与intervals中的四个区间都有至少2个相交的元素。
且这是S最小的情况，故我们输出3。

示例 2:
输入: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
输出: 5
解释:
最小的集合 S = {1, 2, 3, 4, 5}.

注意:
	intervals 的长度范围为[1, 3000]。
	intervals[i] 长度为 2，分别代表左、右边界。
	intervals[i][j] 的值是 [0, 10^8]范围内的整数。
*/

// https://leetcode.com/problems/set-intersection-size-at-least-two/discuss/113085/Ever-wonder-why-the-greedy-algorithm-works-Here-is-the-explanation!/145563
// 抄的
int intersectionSizeTwo(vector<vector<int>>& intervals)
{
	sort(intervals.begin(), intervals.end(),
		[](vector<int> const& a, vector<int> const& b) -> bool
	{
		return (a[1] < b[1]) || (a[1] == b[1] && a[0] > b[0]);
	});
	int m = 0, L = -1, R = -1;
	for (vector<int> const& interval : intervals)
	{
		int a = interval[0], b = interval[1];
		// 两点覆盖
		if (a <= L)
			continue;
		// 一点覆盖
		else if (a <= R)
		{
			m += 1;
			L = R;
			R = b;
		}
		// 区间外面
		else
		{
			m += 2;
			L = b - 1;
			R = b;
		}
	}
	return m;
}


int main()
{
	vector<vector<int>>
		i0 = { { 1, 3 }, { 1, 4 }, { 2, 5 }, { 3, 5 } },
		i1 = { { 1, 2 }, { 2, 3 }, { 2, 4 }, { 4, 5 } };
	OutExpr(intersectionSizeTwo(i0), "%d");
	OutExpr(intersectionSizeTwo(i1), "%d");
}
