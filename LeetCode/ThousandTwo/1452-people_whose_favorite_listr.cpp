#include "leetcode.hpp"

/* 1452. 收藏清单

给你一个数组 favoriteCompanies ，其中 favoriteCompanies[i] 是第 i 名用户收藏的公司清单（下标从 0 开始）。

请找出不是其他任何人收藏的公司清单的子集的收藏清单，并返回该清单下标。
下标需要按升序排列。

示例 1：
输入：favoriteCompanies = [["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]
输出：[0,1,4]
解释：
favoriteCompanies[2]=["google","facebook"] 是 favoriteCompanies[0]=["leetcode","google","facebook"] 的子集。
favoriteCompanies[3]=["google"] 是 favoriteCompanies[0]=["leetcode","google","facebook"] 和 favoriteCompanies[1]=["google","microsoft"] 的子集。
其余的收藏清单均不是其他任何人收藏的公司清单的子集，因此，答案为 [0,1,4] 。

示例 2：
输入：favoriteCompanies = [["leetcode","google","facebook"],["leetcode","amazon"],["facebook","google"]]
输出：[0,1]
解释：favoriteCompanies[2]=["facebook","google"] 是 favoriteCompanies[0]=["leetcode","google","facebook"] 的子集，因此，答案为 [0,1] 。

示例 3：
输入：favoriteCompanies = [["leetcode"],["google"],["facebook"],["amazon"]]
输出：[0,1,2,3]

提示：
	1 <= favoriteCompanies.length <= 100
	1 <= favoriteCompanies[i].length <= 500
	1 <= favoriteCompanies[i][j].length <= 20
	favoriteCompanies[i] 中的所有字符串 各不相同 。
	用户收藏的公司清单也 各不相同 ，也就是说，即便我们按字母顺序排序每个清单， favoriteCompanies[i] != favoriteCompanies[j] 仍然成立。
	所有字符串仅包含小写英文字母。
*/

vector<int> peopleIndexes(vector<vector<string>>& fc)
{
	unordered_map<string, int> S;
	int isi = 0;
	int len = static_cast<int>(fc.size());
	vector<pair<int, vector<int>>> F(len);
	for (int i = 0; i < len; ++i)
	{
		int size = static_cast<int>(fc[i].size());
		for (int k = 0; k < size; ++k)
		{
			auto it = S.find(fc[i][k]);
			if (it == S.end())
			{
				S.emplace(fc[i][k], isi);
				F[i].second.push_back(isi);
				++isi;
			}
			else
				F[i].second.push_back(it->second);
		}
		F[i].first = i;
		sort(F[i].second.begin(), F[i].second.end());
	}
	sort(F.begin(), F.end(),
		[](pair<int, vector<int>>& a, pair<int, vector<int>>& b) -> bool
	{
		return a.second.size() < b.second.size();
	});

	vector<int> ans;
	for (int i = 0; i < len; ++i)
	{
		int di = static_cast<int>(F[i].second.size());
		int const* fi = F[i].second.data();
		for (int k = i + 1; k < len; ++k)
		{
			int dk = static_cast<int>(F[k].second.size());
			int const* fk = F[k].second.data();
			if (di == dk)
				continue;
			if (fi[0] < fk[0] || fi[di - 1] > fk[dk - 1])
				continue;
			int p = 0, q = -1;
			for (; p < di; ++p)
			{
				for (++q; q < dk; ++q)
				{
					if (fi[p] == fk[q])
						break;
				}
				if (q == dk)
					break;
			}
			if (p == di)
			{
				ans.push_back(F[i].first);
				break;
			}
		}
	}

	vector<char> flag(len);
	for (int a : ans)
		flag[a] = 1;
	ans.clear();
	for (int i = 0; i < len; ++i)
	{
		if (!flag[i])
			ans.push_back(i);
	}
	return ans;
}


int main()
{}
