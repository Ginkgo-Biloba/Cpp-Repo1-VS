#include "../srcOld/utility.hpp"

/* 对于一个具有树特征的无向图，我们可选择任何一个节点作为根。
 * 图因此可以成为树，在所有可能的树中，具有最小高度的树被称为最小高度树。
 * 给出这样的一个图，写出一个函数找到所有的最小高度树并返回他们的根节点。
 */

 // 抄的思路
typedef pair<int, int> pairint;

class Solution
{
public:
	vector<vector<int>> nghs;
	vector<int> hist, parents, q;
	int npt, hmax, idxmax;

	void dfs(int start)
	{
		std::fill(hist.begin(), hist.end(), INT_MAX);
		std::fill(parents.begin(), parents.end(), -1);
		q.clear();
		q.push_back(start);
		hist[start] = 0; parents[start] = start;
		hmax = 0;

		for (size_t i = 0; i < q.size(); ++i)
		{
			start = q[i];
			int hcur = hist[start];
			hmax = std::max(hcur, hmax);
			for (int next : nghs[start])
				if (hcur + 1 < hist[next])
				{
					q.push_back(next);
					parents[next] = start;
					hist[next] = hcur + 1;
				}
		}
	}

	vector<int> findMinHeightTrees(int _n, vector<pairint> const& edges)
	{
		vector<int> imid;
		npt = _n;
		if (npt == 1) { imid.push_back(0); return imid; }
		if (npt == 2) { imid.push_back(0); imid.push_back(1); return imid; }

		nghs.clear(); nghs.resize(npt);
		hist.resize(npt);
		parents.resize(npt);
		q.clear(); q.reserve(npt);

		size_t nedge = edges.size();
		for (size_t n = 0; n < nedge; ++n)
		{
			pairint e = edges[n];
			nghs[e.first].push_back(e.second);
			nghs[e.second].push_back(e.first);
		}

		dfs(0);
		idxmax = -1;
		for (int n = 0; n < npt; ++n)
			if (hist[n] == hmax)
			{
				idxmax = n;
				break;
			}

		dfs(idxmax);
		idxmax = -1;
		for (int n = 0; n < npt; ++n)
			if (hist[n] == hmax)
			{
				idxmax = n;
				break;
			}

		// 找中点
		for (int n = 0; n < (hmax / 2); ++n)
			idxmax = parents[idxmax];
		imid.push_back(idxmax);
		if (hmax & 1)
			imid.push_back(parents[idxmax]);

		return imid;
	}
};


int main()
{
	vector<pairint> edges =
	{
		{ 0, 1 }, { 0, 2 }, { 0, 3 }, { 3, 4 }, { 3, 5 },
		{ 1, 6 }, { 4, 7 }, { 2, 8 }, { 0, 9 }, { 0, 10 }, { 2, 11 }
	};

	vector<int> idxh = Solution().findMinHeightTrees(12, edges);
	output(idxh, "findMinHeightTrees");
}

