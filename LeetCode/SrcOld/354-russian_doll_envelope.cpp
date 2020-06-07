#include "leetcode.hpp"

/* 354. 俄罗斯套娃信封问题

给定一些标记了宽度和高度的信封，宽度和高度以整数对形式 (w, h) 出现。
当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。

请计算最多能有多少个信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。

说明:
不允许旋转信封。

示例:
输入: envelopes = [[5,4],[6,4],[6,7],[2,3]]
输出: 3
解释: 最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
*/

//https://leetcode.com/problems/russian-doll-envelopes/discuss/82763/Java-NLogN-Solution-with-Explanation
// 抄的。排序，然后最长递增子序列
int maxEnvelopes(vector<vector<int>>& E)
{
	int len = static_cast<int>(E.size());
	vector<int> S;
	sort(E.begin(), E.end(),
		[](vector<int>& a, vector<int>& b) -> bool
	{
		return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
	});
	for (int i = 0; i < len; ++i)
	{
		auto it = lower_bound(S.begin(), S.end(), E[i][1]);
		if (it == S.end())
			S.push_back(E[i][1]);
		else
			*it = E[i][1];
	}
	return static_cast<int>(S.size());
}

// 不允许旋转这个条件是后来加上去的，最初题目里面没有。
// 如果允许，则只有 N^2 的方法。
int maxEnvelopes2(vector<vector<int>>& E)
{
	int len = static_cast<int>(E.size());
	vector<int> dp(len, 1);
	sort(E.begin(), E.end());
	for (int k = 1; k < len; ++k)
		for (int i = 0; i < k; ++i)
		{
			if ((E[i][0] < E[k][0] && E[i][1] < E[k][1])
				|| (E[i][0] < E[k][1] && E[i][1] < E[k][0]))
				dp[k] = max(dp[k], 1 + dp[i]);
		}
	int ans = 0;
	for (int i = 0; i < len; ++i)
		ans = max(ans, dp[i]);
	return ans;
}


int main()
{
	vector<vector<int>>
		a = { { 5, 4 }, { 6, 4 }, { 6, 7 }, { 2, 3 } },
		b = { { 1, 3 }, { 3, 5 }, { 6, 7 }, { 6, 8 }, { 8, 4 }, { 9, 5 } };
	OutExpr(maxEnvelopes(a), "%d");
	OutExpr(maxEnvelopes(b), "%d");
}
