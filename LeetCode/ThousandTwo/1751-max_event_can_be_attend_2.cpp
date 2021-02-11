#include "leetcode.hpp"

/* 1751. 最多可以参加的会议数目 II

给你一个 events 数组，其中 events[i] = [startDayi, endDayi, valuei] ，表示第 i 个会议在 startDayi 天开始，第 endDayi 天结束，如果你参加这个会议，你能得到价值 valuei 。
同时给你一个整数 k 表示你能参加的最多会议数目。

你同一时间只能参加一个会议。
如果你选择参加某个会议，那么你必须 完整 地参加完这个会议。
会议结束日期是包含在会议内的，也就是说你不能同时参加一个开始日期与另一个结束日期相同的两个会议。

请你返回能得到的会议价值 最大和 。

示例 1：
https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60048-pm.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/02/06/screenshot-2021-01-11-at-60048-pm.png
输入：events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
输出：7
解释：选择绿色的活动会议 0 和 1，得到总价值和为 4 + 3 = 7 。

示例 2：
https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60150-pm.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/02/06/screenshot-2021-01-11-at-60150-pm.png
输入：events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
输出：10
解释：参加会议 2 ，得到价值和为 10 。
你没法再参加别的会议了，因为跟会议 2 有重叠。
你 不 需要参加满 k 个会议。

示例 3：
https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-60703-pm.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/02/06/screenshot-2021-01-11-at-60703-pm.png
输入：events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
输出：9
解释：尽管会议互不重叠，你只能参加 3 个会议，所以选择价值最大的 3 个会议。

提示：
	1 <= k <= events.length
	1 <= k * events.length <= 10^6
	1 <= startDayi <= endDayi <= 10^9
	1 <= valuei <= 10^6
*/

// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/discuss/1052581/Python-DP
// 抄的
int maxValue(vector<vector<int>>& A, int k)
{
	vector<array<int, 2>> dp, eq;
	dp.push_back({ 0, 0 });
	sort(A.begin(), A.end(),
		[](vector<int>& a, vector<int>& b) -> bool
	{
		return a[1] < b[1];
	});
	while (k--)
	{
		eq.clear();
		eq.push_back({ 0, 0 });
		for (auto const& a : A)
		{
			array<int, 2> e = { a[0], -1 };
			auto it = lower_bound(dp.begin(), dp.end(), e) - 1;
			if (it->at(1) + a[2] > eq.back()[1])
				eq.push_back({ a[1], it->at(1) + a[2] });
		}
		dp.swap(eq);
	}
	return dp.back()[1];
}


int main()
{
	vector<vector<int>>
		a = { { 1, 2, 4 }, { 3, 4, 3 }, { 2, 3, 1 } },
		b = { { 1, 2, 4 }, { 3, 4, 3 }, { 2, 3, 10 } },
		c = { { 1, 1, 1 }, { 2, 2, 2 }, { 3, 3, 3 }, { 4, 4, 4 } };
	OutExpr(maxValue(a, 2), "%d");
	OutExpr(maxValue(b, 2), "%d");
	OutExpr(maxValue(c, 3), "%d");
}
