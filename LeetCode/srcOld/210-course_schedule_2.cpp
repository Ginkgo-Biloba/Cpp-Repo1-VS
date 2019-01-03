#include "../src/utility.hpp"

typedef vector<pair<int, int>> vecpair;

/** �������涼˵���������򣬱Ͼ���һ����Ҫ��
 * ��ʵ����Ҳ���Լ������ͼ��û�л� */
bool canFinish(int const numCrs, vecpair const& requires)
{
	vector<vector<char>> before(numCrs, vector<char>(numCrs));
	vector<int> indegree(numCrs);
	pair<int, int> cond;
	size_t len = requires.size();

	for (size_t i = 0; i < len; ++i)
	{
		// ����ǰ��ģ���Ҫ����ɺ����
		cond = requires[i];
		// if Ϊ�˴����ظ����
		if (before[cond.second][cond.first] == 0)
			++(indegree[cond.first]);
		before[cond.second][cond.first] = 1;
	}

	size_t finish = 0;
	// ��ʵӦ���ö��еģ����Ƿ����ֲ�����ǰ���
	vector<int> take; take.reserve(numCrs);
	for (int i = 0; i < numCrs; ++i)
	{
		// ����Ҫ�κ����пγ�
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
				// ���пγ��Ѿ�����
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
		// ����ǰ��ģ���Ҫ����ɺ����
		cond = requires[i];
		// if Ϊ�˴����ظ����
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
				// ���пγ��Ѿ�����
				if (indegree[i] == 0)
					take.push_back(i);
			}
		}
	}

	// �겻�ɷ��ؿյ�
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
