#include "leetcode.hpp"

/* 332. 重新安排行程

给定一个机票的字符串二维数组 [from, to]，子数组中的两个成员分别表示飞机出发和降落的机场地点，对该行程进行重新规划排序。
所有这些机票都属于一个从JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 出发。

说明:
	如果存在多种有效的行程，你可以按字符自然排序返回最小的行程组合。
	例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。
	所有的机场都用三个大写字母表示（机场代码）。
	假定所有机票至少存在一种合理的行程。

示例 1:
输入: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
输出: ["JFK", "MUC", "LHR", "SFO", "SJC"]

示例 2:
输入: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
输出: ["JFK","ATL","JFK","SFO","ATL","SFO"]
解释: 另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"]。
但是它自然排序更大更靠后。
*/

// https://leetcode.com/problems/reconstruct-itinerary/discuss/78842/C%2B%2B-non-recursive-O(N)-time-O(N)-space-solution-with-detail-explanations
// 抄的
vector<string> findItinerary(vector<vector<string>>& tickets)
{
	unordered_map<string, std::multiset<string>> m;
	for (auto& t : tickets)
		m[t[0]].insert(t[1]);

	vector<string> march = { "JFK" };
	vector<string> ans;

	while (!march.empty())
	{
		string& from = march.back();
		auto it = m.find(from);
		if (it != m.end() && !(it->second.empty()))
		{
			march.push_back(*(it->second.begin()));
			it->second.erase(it->second.begin());
		}
		else
		{
			ans.push_back(from);
			march.pop_back();
		}
	}

	reverse(ans.begin(), ans.end());
	return ans;
}


int main()
{
	vector<vector<string>>
		a = {
			{ "MUC", "LHR" },
			{ "JFK", "MUC" },
			{ "SFO", "SJC" },
			{ "LHR", "SFO" },
	},
	b = {
		{ "JFK", "SFO" },
		{ "JFK", "ATL" },
		{ "SFO", "ATL" },
		{ "ATL", "JFK" },
		{ "ATL", "SFO" },
	};
	output(findItinerary(a), ", ");
	output(findItinerary(b), ", ");
}
