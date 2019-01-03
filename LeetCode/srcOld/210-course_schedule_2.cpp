#include "../src/utility.hpp"

typedef vector<pair<int, int>> vecpair;

/** 评论里面都说用拓扑排序，毕竟下一道题要用
 * 其实这里也可以检测有向图有没有环 */
bool canFinish(int const numCrs, vecpair const& requires)
{
	vector<vector<char>> before(numCrs, vector<char>(numCrs));
	vector<int> indegree(numCrs);
	pair<int, int> cond;
	size_t len = requires.size();

	for (size_t i = 0; i < len; ++i)
	{
		// 进行前面的，需要先完成后面的
		cond = requires[i];
		// if 为了处理重复情况
		if (before[cond.second][cond.first] == 0)
			++(indegree[cond.first]);
		before[cond.second][cond.first] = 1;
	}

	size_t finish = 0;
	// 其实应该用队列的，但是反正又不用往前填充
	vector<int> take; take.reserve(numCrs);
	for (int i = 0; i < numCrs; ++i)
	{
		// 不需要任何先行课程
		if (indegree[i] == 0)
			take.push_back(i);
	}

	while (finish < take.size())
	{
		int course = take[finish]; ++finish;
		for (int i = 0; i < numCrs; ++i)
		{
			if (before[course][i])
			{
				--(indegree[i]);
				// 先行课程已经结束
				if (indegree[i] == 0)
					take.push_back(i);
			}
		}
	}

	return static_cast<int>(finish) == numCrs;
}


vector<int> findOrder(int const numCrs, vecpair const& requires)
{
	vector<vector<char>> before(numCrs, vector<char>(numCrs));
	pair<int, int> cond;
	vector<int> indegree(numCrs);
	size_t len = requires.size();

	for (size_t i = 0; i < len; ++i)
	{
		// 进行前面的，需要先完成后面的
		cond = requires[i];
		// if 为了处理重复情况
		if (before[cond.second][cond.first] == 0)
			++(indegree[cond.first]);
		before[cond.second][cond.first] = 1;
	}

	vector<int> take; take.reserve(numCrs);
	size_t finish = 0;
	for (int i = 0; i < numCrs; ++i)
	{
		if (indegree[i] == 0)
			take.push_back(i);
	}

	while (finish < take.size())
	{
		int course = take[finish]; ++finish;
		for (int i = 0; i < numCrs; ++i)
		{
			if (before[course][i])
			{
				--(indegree[i]);
				// 先行课程已经结束
				if (indegree[i] == 0)
					take.push_back(i);
			}
		}
	}

	// 完不成返回空的
	if (static_cast<int>(finish) != numCrs)
		take.clear();
	return take;
}



int main()
{
	vecpair requires = { { 1, 0 }, { 2, 0 }, { 3, 1 }, { 3, 2 } };
	bool can = canFinish(4, requires);
	printf("%1s = %s\n", "canFinish", (can ? "T" : "F"));
	vector<int> order = findOrder(4, requires);
	output(order, "findOrder");
}
