#include "leetcode.hpp"

/* 207. 课程表

你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。

在选修某些课程之前需要一些先修课程。
例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]

给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？

示例 1:
输入: 2, [[1,0]]
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。
所以这是可能的。

示例 2:
输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。
学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。
这是不可能的。

提示：
	输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。
	详情请参见图的表示法。
	你可以假定输入的先决条件中没有重复的边。
	1 <= numCourses <= 10^5
*/

bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
	vector<int> req(numCourses), cur, ans;
	vector<vector<int>> adj(numCourses);
	for (auto& p : prerequisites)
	{
		req[p[0]] += 1;
		adj[p[1]].push_back(p[0]);
	}
	for (int i = 0; i < numCourses; ++i)
	{
		if (req[i] == 0)
			cur.push_back(i);
	}
	for (size_t d = 0; d < cur.size(); ++d)
	{
		vector<int>& ngh = adj[cur[d]];
		for (int n : ngh)
		{
			req[n] -= 1;
			if (req[n] == 0)
				cur.push_back(n);
		}
	}
	return static_cast<int>(cur.size()) == numCourses;
}


int main()
{
	vector<vector<int>>
		a = { { 1, 0 } },
		b = { { 1, 0 }, { 0, 1 } };
	OutBool(canFinish(2, a));
	OutBool(canFinish(2, b));
}
