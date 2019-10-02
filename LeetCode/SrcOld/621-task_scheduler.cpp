#include "leetcode.hpp"

/* 621. 任务调度器

给定一个用字符数组表示的 CPU 需要执行的任务列表。
其中包含使用大写的 A - Z 字母表示的26 种不同种类的任务。
任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。
CPU 在任何一个单位时间内都可以执行一个任务，或者在待命状态。

然而，两个相同种类的任务之间必须有长度为 n 的冷却时间。
因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。

你需要计算完成所有任务所需要的最短时间。

示例 1：
输入: tasks = ["A","A","A","B","B","B"], n = 2
输出: 8
执行顺序: A -> B -> (待命) -> A -> B -> (待命) -> A -> B.

注：
	任务的总个数为 [1, 10000]。
	n 的取值范围为 [0, 100]。
*/

// https://leetcode.com/problems/task-scheduler/discuss/104507/Python-Straightforward-with-Explanation
// 抄的
int leastInterval(vector<char>& tasks, int n)
{
	int len = static_cast<int>(tasks.size());
	int count[26];
	int nmax = 0, vmax = 0;
	memset(count, 0, sizeof(count));
	for (int i = 0; i < len; ++i)
		count[tasks[i] - 'A'] += 1;
	for (int i = 0; i < 26; ++i)
	{
		if (vmax < count[i])
		{
			vmax = count[i];
			nmax = 1;
		}
		else if (vmax == count[i])
			++nmax;
	}

	vmax = (vmax - 1) * (n + 1) + nmax;
	return std::max(vmax, len);
}


int main()
{
	vector<char> tasks = { 'A', 'A', 'A', 'B', 'B', 'B' };
	OutExpr(leastInterval(tasks, 2), "%d");
}
