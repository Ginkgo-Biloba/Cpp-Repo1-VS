#include "leetcode.hpp"

/* 1744. 你能在你最喜欢的那天吃到你最喜欢的糖果吗？

给你一个下标从 0 开始的正整数数组 candiesCount ，其中 candiesCount[i] 表示你拥有的第 i 类糖果的数目。
同时给你一个二维数组 queries ，其中 queries[i] = [favoriteTypei, favoriteDayi, dailyCapi] 。

你按照如下规则进行一场游戏：
	你从第 0 天开始吃糖果。
	你在吃完 所有 第 i - 1 类糖果之前，不能 吃任何一颗第 i 类糖果。
	在吃完所有糖果之前，你必须每天 至少 吃 一颗 糖果。

请你构建一个布尔型数组 answer ，满足 answer.length == queries.length 。
answer[i] 为 true 的条件是：在每天吃 不超过 dailyCapi 颗糖果的前提下，你可以在第 favoriteDayi 天吃到第 favoriteTypei 类糖果；否则 answer[i] 为 false 。
注意，只要满足上面 3 条规则中的第二条规则，你就可以在同一天吃不同类型的糖果。

请你返回得到的数组 answer 。

示例 1：
输入：candiesCount = [7,4,5,3,8], queries = [[0,2,2],[4,2,4],[2,13,1000000000]]
输出：[true,false,true]
提示：
1- 在第 0 天吃 2 颗糖果(类型 0），第 1 天吃 2 颗糖果（类型 0），第 2 天你可以吃到类型 0 的糖果。
2- 每天你最多吃 4 颗糖果。即使第 0 天吃 4 颗糖果（类型 0），第 1 天吃 4 颗糖果（类型 0 和类型 1），你也没办法在第 2 天吃到类型 4 的糖果。换言之，你没法在每天吃 4 颗糖果的限制下在第 2 天吃到第 4 类糖果。
3- 如果你每天吃 1 颗糖果，你可以在第 13 天吃到类型 2 的糖果。

示例 2：
输入：candiesCount = [5,2,6,4,1], queries = [[3,1,2],[4,10,3],[3,10,100],[4,100,30],[1,3,1]]
输出：[false,true,true,false,false]

提示：
	1 <= candiesCount.length <= 10^5
	1 <= candiesCount[i] <= 10^5
	1 <= queries.length <= 10^5
	queries[i].length == 3
	0 <= favoriteTypei < candiesCount.length
	0 <= favoriteDayi <= 10^9
	1 <= dailyCapi <= 10^9
*/

// https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/discuss/1042983/Python-Prifix-Sum
// 抄的
vector<bool> canEat(vector<int>& candy, vector<vector<int>>& query)
{
	vector<bool> ans;
	vector<int64_t> a = { 0 };
	int64_t cur = 0;
	for (int c : candy)
		a.push_back(cur += c);
	for (auto& q : query)
	{
		int type = q[0];
		int64_t day = q[1];
		int64_t cap = q[2];
		ans.push_back((a[type] / cap <= day) && (day < a[type + 1]));
	}
	return ans;
}

vector<bool> canEat0(vector<int>& candy, vector<vector<int>>& query)
{
	int len = static_cast<int>(candy.size());
	vector<int64_t> a;
	int64_t lo = 0, hi = 0;
	for (int i = 0; i < len; ++i)
	{
		hi += candy[i];
		a.push_back(hi);
	}
	vector<bool> ans;
	for (auto& q : query)
	{
		ptrdiff_t type = q[0];
		int64_t day = q[1];
		int64_t cap = q[2];
		lo = day + 1;
		hi = (day + 1) * cap;
		auto ilo = lower_bound(a.begin(), a.end(), lo) - a.begin();
		auto ihi = lower_bound(a.begin(), a.end(), hi) - a.begin();
		ans.push_back(ilo <= type && type <= ihi);
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 7, 4, 5, 3, 8 },
		b = { 5, 2, 6, 4, 1 };
	vector<vector<int>>
		h = { { 0, 2, 2 }, { 4, 2, 4 }, { 2, 13, 1000000000 } },
		i = { { 3, 1, 2 }, { 4, 10, 3 }, { 3, 10, 100 }, { 4, 100, 30 }, { 1, 3, 1 } };
	canEat(a, h);
	canEat(b, i);
}
