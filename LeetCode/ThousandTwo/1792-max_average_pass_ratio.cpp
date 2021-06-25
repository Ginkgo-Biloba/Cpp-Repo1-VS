#include "leetcode.hpp"

/* 1792. 最大平均通过率

一所学校里有一些班级，每个班级里有一些学生，现在每个班都会进行一场期末考试。
给你一个二维数组 classes ，其中 classes[i] = [passi, totali] ，表示你提前知道了第 i 个班级总共有 totali 个学生，其中只有 passi 个学生可以通过考试。

给你一个整数 extraStudents ，表示额外有 extraStudents 个聪明的学生，他们 一定 能通过任何班级的期末考。
你需要给这 extraStudents 个学生每人都安排一个班级，使得 所有 班级的 平均 通过率 最大 。

一个班级的 通过率 等于这个班级通过考试的学生人数除以这个班级的总人数。
平均通过率 是所有班级的通过率之和除以班级数目。

请你返回在安排这 extraStudents 个学生去对应班级后的 最大 平均通过率。
与标准答案误差范围在 10-5 以内的结果都会视为正确结果。

示例 1：
输入：classes = [[1,2],[3,5],[2,2]], extraStudents = 2
输出：0.78333
解释：你可以将额外的两个学生都安排到第一个班级，平均通过率为 (3/4 + 3/5 + 2/2) / 3 = 0.78333 。

示例 2：
输入：classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
输出：0.53485

提示：
	1 <= classes.length <= 10^5
	classes[i].length == 2
	1 <= passi <= totali <= 10^5
	1 <= extraStudents <= 10^5
*/

double maxAverageRatio(vector<vector<int>>& classes, int extraStudents)
{
	struct Elem
	{
		int a, b;
		double d;
		Elem(int pass, int total)
			: a(pass)
			, b(total)
		{
			d = (a + 1.0) / (b + 1.0) - (static_cast<double>(a) / b);
		}
		bool operator<(Elem const& e)
		{
			return d < e.d;
		}
	};

	vector<Elem> E;
	E.reserve(classes.size());
	for (auto const& c : classes)
		E.emplace_back(c[0], c[1]);
	make_heap(E.begin(), E.end());

	while (extraStudents--)
	{
		pop_heap(E.begin(), E.end());
		Elem e = E.back();
		E.back() = Elem(e.a + 1, e.b + 1);
		push_heap(E.begin(), E.end());
	}

	double ratio = 0;
	for (auto const& e : E)
		ratio += static_cast<double>(e.a) / e.b;
	return ratio / static_cast<int>(E.size());
}


int main()
{}
