#include "leetcode.hpp"

/* 1326. 灌溉花园的最少水龙头数目

在 x 轴上有一个一维的花园。花园长度为 n，从点 0 开始，到点 n 结束。

花园里总共有 n + 1 个水龙头，分别位于 [0, 1, ..., n] 。

给你一个整数 n 和一个长度为 n + 1 的整数数组 ranges，其中 ranges[i] （下标从 0 开始）表示：如果打开点 i 处的水龙头，可以灌溉的区域为 [i -  ranges[i], i + ranges[i]] 。

请你返回可以灌溉整个花园的 最少水龙头数目 。如果花园始终存在无法灌溉到的地方，请你返回 -1 。


示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/19/1685_example_1.png
输入：n = 5, ranges = [3,4,1,1,0,0]
输出：1
解释：
点 0 处的水龙头可以灌溉区间 [-3,3]
点 1 处的水龙头可以灌溉区间 [-3,5]
点 2 处的水龙头可以灌溉区间 [1,3]
点 3 处的水龙头可以灌溉区间 [2,4]
点 4 处的水龙头可以灌溉区间 [4,4]
点 5 处的水龙头可以灌溉区间 [5,5]
只需要打开点 1 处的水龙头即可灌溉整个花园 [0,5] 。

示例 2：
输入：n = 3, ranges = [0,0,0,0]
输出：-1
解释：即使打开所有水龙头，你也无法灌溉整个花园。

示例 3：
输入：n = 7, ranges = [1,2,1,0,2,1,0,1]
输出：3

示例 4：
输入：n = 8, ranges = [4,0,0,0,0,0,0,0,4]
输出：2

示例 5：
输入：n = 8, ranges = [4,0,0,0,4,0,0,0,4]
输出：1

提示：
	1 <= n <= 10^4
	ranges.length == n + 1
	0 <= ranges[i] <= 100
*/

int minTaps(int n, vector<int>& ranges)
{
	vector<pair<int, int>> rng;
	int L = 0, R = 0, cur = 0, len = INT_MAX;
	rng.reserve(n);
	for (int i = 0; i <= n; ++i)
		if (ranges[i] > 0)
		{
			L = max(i - ranges[i], 0);
			R = min(i + ranges[i], n);
			len = min(len, L);
			cur = max(cur, R);
			rng.emplace_back(L, R);
		}
	if (0 < len || cur < n)
		return -1;

	cur = 0;
	len = static_cast<int>(rng.size());
	/*
	sort(rng.begin(), rng.end(),
		[](pair<int, int> const& a, pair<int, int> const& b) {
			return a.first < b.first
				|| (a.first == b.first && a.second > b.second);
		});
	vector<int> buf(n + 1, INT_MAX - n - 1);
	buf[0] = 0;
	for (int i = 0; i < len; ++i)
	{
		if (rng[i].second <= cur)
			continue;
		L = rng[i].first;
		R = rng[i].second;
		int k = buf[L] + 1;
		for (++L; L <= R; ++L)
			buf[L] = min(buf[L], k);
	}
	return buf[n] <= n ? buf[n] : -1;
	*/
	sort(rng.begin(), rng.end(),
		[](pair<int, int> const& a, pair<int, int> const& b)
	{
		return a.first < b.first;
	});
	priority_queue<int> Q;
	L = R = cur = 0;
	for (int i = 0; (i < len) && (L < n); ++cur)
	{
		for (; (i < len) && (rng[i].first <= L); ++i)
			Q.push(rng[i].second);
		R = Q.top();
		// Q.pop(); // 无所谓
		if (L == R)
			break;
		L = R;
	}
	return L >= n ? cur : -1;
}


int main()
{
	vector<int>
		a = { 3, 4, 1, 1, 0, 0 },
		b = { 0, 0, 0, 0 },
		c = { 1, 2, 1, 0, 2, 1, 0, 1 },
		d = { 4, 0, 0, 0, 0, 0, 0, 0, 4 },
		e = { 4, 0, 0, 0, 4, 0, 0, 0, 4 };
	OutExpr(minTaps(5, a), "%d");
	OutExpr(minTaps(3, b), "%d");
	OutExpr(minTaps(7, c), "%d");
	OutExpr(minTaps(8, d), "%d");
	OutExpr(minTaps(8, e), "%d");
}
