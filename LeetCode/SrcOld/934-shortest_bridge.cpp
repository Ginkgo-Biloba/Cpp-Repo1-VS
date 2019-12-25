#include "leetcode.hpp"

/* 934. 最短的桥

在给定的二维二进制数组 A 中，存在两座岛。
岛是由四面相连的 1 形成的一个最大组。

现在，我们可以将 0 变为 1，以使两座岛连接起来，变成一座岛。

返回必须翻转的 0 的最小数目。可以保证答案至少是 1。

示例 1：
输入：[[0,1],[1,0]]
输出：1

示例 2：
输入：[[0,1,0],[0,0,0],[0,0,1]]
输出：2

示例 3：
输入：[[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
输出：1

提示：
	1 <= A.length = A[0].length <= 100
	A[i][j] == 0 或 A[i][j] == 1
*/

int shortestBridge(vector<vector<int>>& A)
{
	int const dir[] = { -1, 0, 1, 0, -1 };
	vector<pair<int, int>> cur, nxt;
	int step = 1;
	int len = static_cast<int>(A.size());
	unsigned ulen = len;

	// 干掉第一个
	for (int h = 0; h < len; ++h)
		for (int w = 0; w < len; ++w)
		{
			if (A[h][w])
			{
				step = 0;
				cur.emplace_back(h, w);
				A[h][w] = -len;
			}
			while (!cur.empty())
			{
				nxt.clear();
				for (auto c : cur)
					for (int d = 0; d < 4; ++d)
					{
						int y = c.first + dir[d];
						int x = c.second + dir[d + 1];
						if (static_cast<unsigned>(y) < ulen
							&& static_cast<unsigned>(x) < ulen
							&& A[y][x] == 1)
						{
							A[y][x] = -len;
							nxt.emplace_back(y, x);
						}
					}
				nxt.swap(cur);
			}
			if (step == 0)
				h = w = len;
		}

	// 记住第二个，广搜。图大的话，用距离变换好些
	for (int h = 0; h < len; ++h)
		for (int w = 0; w < len; ++w)
		{
			if (A[h][w] == 1)
				cur.emplace_back(h, w);
		}

	step = 0;
	while (!cur.empty())
	{
		++step;
		nxt.clear();
		for (auto c : cur)
			for (int d = 0; d < 4; ++d)
			{
				int y = c.first + dir[d];
				int x = c.second + dir[d + 1];
				if (static_cast<unsigned>(y) >= ulen
					|| static_cast<unsigned>(x) >= ulen
					|| A[y][x] == 1)
					continue;
				if (A[y][x] < 0)
					return step - 1;
				A[y][x] = 1;
				nxt.emplace_back(y, x);
			}
		nxt.swap(cur);
	}
	return step;
}

int main()
{
	vector<vector<int>>
		a = { { 0, 1 }, { 1, 0 } },
		b = { { 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 1 } },
		c = {
			{ 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 0, 1 },
			{ 1, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 1 },
	};
	OutExpr(shortestBridge(a), "%d");
	OutExpr(shortestBridge(b), "%d");
	OutExpr(shortestBridge(c), "%d");
}
