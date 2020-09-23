#include "leetcode.hpp"

/* 913. 猫和老鼠

两个玩家分别扮演猫（Cat）和老鼠（Mouse）在无向图上进行游戏，他们轮流行动。

该图按下述规则给出：graph[a] 是所有结点 b 的列表，使得 ab 是图的一条边。

老鼠从结点 1 开始并率先出发，猫从结点 2 开始且随后出发，在结点 0 处有一个洞。

在每个玩家的回合中，他们必须沿着与他们所在位置相吻合的图的一条边移动。
例如，如果老鼠位于结点 1，那么它只能移动到 graph[1] 中的（任何）结点去。

此外，猫无法移动到洞（结点 0）里。

然后，游戏在出现以下三种情形之一时结束：
	如果猫和老鼠占据相同的结点，猫获胜。
	如果老鼠躲入洞里，老鼠获胜。
	如果某一位置重复出现（即，玩家们的位置和移动顺序都与上一个回合相同），游戏平局。

给定 graph，并假设两个玩家都以最佳状态参与游戏，如果老鼠获胜，则返回 1；如果猫获胜，则返回 2；如果平局，则返回 0。

示例：

输入：[[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
输出：0
解释：
|   4---3---1
|   |   |
|   2---5
|    \ /
|     0

提示：
	3 <= graph.length <= 200
	保证 graph[1] 非空。
	保证 graph[2] 包含非零元素。
*/

// https://leetcode.com/problems/cat-and-mouse/discuss/176177/Most-of-the-DFS-solutions-are-WRONG-check-this-case
// 抄的
int catMouseGame(vector<vector<int>>& graph)
{
	int n = static_cast<int>(graph.size());
	// cat, mouse, mouseMove
	int colour[50][50][2], outdeg[50][50][2];
	memset(colour, 0, sizeof(colour));
	memset(outdeg, 0, sizeof(outdeg));

	for (int i = 0; i < n; ++i) // cat
		for (int j = 0; j < n; ++j) // mouse
		{
			outdeg[i][j][0] = static_cast<int>(graph[j].size());
			outdeg[i][j][1] = static_cast<int>(graph[i].size());
			for (int k : graph[i])
				if (k == 0)
				{
					--(outdeg[i][j][1]);
					break;
				}
		}

	typedef std::array<int, 4> vsi4;
	std::deque<vsi4> q;
	for (int k = 1; k < n; ++k)
		for (int m = 0; m < 2; ++m)
		{
			colour[k][0][m] = 1;
			q.push_back({ k, 0, m, 1 });
			colour[k][k][m] = 2;
			q.push_back({ k, k, m, 2 });
		}

	while (!q.empty())
	{
		vsi4 cur = q.front();
		int cat = cur[0], mouse = cur[1], mMove = cur[2], c = cur[3];
		q.pop_front();
		if (cat == 2 && mouse == 1 && mMove == 0)
			return c;
		int prevMove = 1 - mMove;
		vector<int>& prevGraph = graph[prevMove == 1 ? cat : mouse];
		for (int prev : prevGraph)
		{
			int prevCat = prevMove == 1 ? prev : cat;
			int prevMouse = prevMove == 1 ? mouse : prev;
			if (prevCat == 0)
				continue;
			if (colour[prevCat][prevMouse][prevMove] > 0)
				continue;
			if ((prevMove == 1 && c == 2)
				|| (prevMove == 0 && c == 1)
				|| (--(outdeg[prevCat][prevMouse][prevMove]) == 0))
			{
				colour[prevCat][prevMouse][prevMove] = c;
				q.push_back({ prevCat, prevMouse, prevMove, c });
			}
		}
	}

	return colour[2][1][0];
}


int main()
{
	vector<vector<int>>
		a = { { 2, 5 }, { 3 }, { 0, 4, 5 }, { 1, 4, 5 }, { 2, 3 }, { 0, 2, 3 } };
	OutExpr(catMouseGame(a), "%d");
}
