#include "leetcode.hpp"

/* 49. 字母异位词分组

给定一个字符串数组，将字母异位词组合在一起。
字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
输出:
[
	["ate","eat","tea"],
	["nat","tan"],
	["bat"]
]

说明：
	所有输入均为小写字母。
	不考虑答案输出的顺序。
*/

vector<vector<string>> groupAnagrams(vector<string>& S)
{
	vector<vector<string>> R;
	unordered_map<string, vector<string>> M;
	for (string s : S)
	{
		string t = s;
		sort(t.begin(), t.end());
		M[t].push_back(s);
	}
	size_t r = 0;
	R.resize(M.size());
	for (auto& kv : M)
		R[r++].swap(kv.second);
	return R;
}


int main()
{}
