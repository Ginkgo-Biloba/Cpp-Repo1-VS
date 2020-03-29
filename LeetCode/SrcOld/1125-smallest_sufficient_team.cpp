#include "leetcode.hpp"

/* 1125. 最小的必要团队

作为项目经理，你规划了一份需求的技能清单 req_skills，并打算从备选人员名单 people 中选出些人组成一个「必要团队」（ 编号为 i 的备选人员 people[i] 含有一份该备选人员掌握的技能列表）。

所谓「必要团队」，就是在这个团队中，对于所需求的技能列表 req_skills 中列出的每项技能，团队中至少有一名成员已经掌握。

我们可以用每个人的编号来表示团队中的成员：例如，团队 team = [0, 1, 3] 表示掌握技能分别为 people[0]，people[1]，和 people[3] 的备选人员。

请你返回 任一 规模最小的必要团队，团队成员用人员编号表示。你可以按任意顺序返回答案，本题保证答案存在。

示例 1：
输入：req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
输出：[0,2]

示例 2：
输入：req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
输出：[1,2]

提示：
	1 <= req_skills.length <= 16
	1 <= people.length <= 60
	1 <= people[i].length, req_skills[i].length, people[i][j].length <= 16
	req_skills 和 people[i] 中的元素分别各不相同
	req_skills[i][j], people[i][j][k] 都由小写英文字母组成
	本题保证「必要团队」一定存在
*/

// https://leetcode.com/problems/smallest-sufficient-team/discuss/334832/c%2B%2B-dp-bitmask-solution-with-algorithm
// 抄的
class Solution
{
public:
	vector<int> smallestSufficientTeam(
		vector<string>& req_skills,
		vector<vector<string>>& people)
	{
		int const n = static_cast<int>(req_skills.size());
		int const m = static_cast<int>(people.size());
		unordered_map<string, int> skm;
		std::map<int, vector<int>> ans;
		skm.reserve(1 << n);
		for (int i = 0; i < n; ++i)
			skm[req_skills[i]] = i;

		ans[0] = {};
		for (int i = 0; i < m; ++i)
		{
			int cur = 0;
			for (string const& p : people[i])
				cur |= (1 << skm[p]);
			for (auto it = ans.begin(); it != ans.end(); ++it)
			{
				int with = it->first | cur;
				auto iaw = ans.find(with);
				if (iaw == ans.end()
					|| iaw->second.size() > 1 + it->second.size())
				{
					ans[with] = it->second;
					ans[with].push_back(i);
				}
			}
		}
		return ans[(1 << n) - 1];
	}
};


int main()
{
	vector<string> req = { "algorithms", "math", "java", "reactjs", "csharp", "aws" };
	vector<vector<string>> people = {
		{ "algorithms", "math", "java" },
		{ "algorithms", "math", "reactjs" },
		{ "java", "csharp", "aws" },
		{ "reactjs", "csharp" },
		{ "csharp", "math" },
		{ "aws", "java" }
	};
	Solution s;
	output(s.smallestSufficientTeam(req, people));
}
