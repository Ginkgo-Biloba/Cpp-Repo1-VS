#include "leetcode.hpp"

/* 864. 获取所有钥匙的最短路径

给定一个二维网格 grid。
"." 代表一个空房间，"#" 代表一堵墙，"@" 是起点，（"a", "b", ...）代表钥匙，（"A", "B", ...）代表锁。

我们从起点开始出发，一次移动是指向四个基本方向之一行走一个单位空间。
我们不能在网格外面行走，也无法穿过一堵墙。如果途经一个钥匙，我们就把它捡起来。
除非我们手里有对应的钥匙，否则无法通过锁。

假设 K 为钥匙/锁的个数，且满足 1 <= K <= 6，字母表中的前 K 个字母在网格中都有自己对应的一个小写和一个大写字母。
换言之，每个锁有唯一对应的钥匙，每个钥匙也有唯一对应的锁。
另外，代表钥匙和锁的字母互为大小写并按字母顺序排列。

返回获取所有钥匙所需要的移动的最少次数。如果无法获取所有钥匙，返回 -1 。

示例 1：
输入：["@.a.#","###.#","b.A.B"]
输出：8

示例 2：
输入：["@..aA","..B#.","....b"]
输出：6

提示：
	1 <= grid.length <= 30
	1 <= grid[0].length <= 30
	grid[i][j] 只含有 '.', '#', '@', 'a'-'f' 以及 'A'-'F'
	钥匙的数目范围是 [1, 6]，每个钥匙都对应一个不同的字母，正好打开一个对应的锁。
*/


// https://leetcode.com/problems/shortest-path-to-get-all-keys/discuss/146878/Java-BFS-Solution
// 抄的
class Solution
{
	struct state
	{
		int key, row, col;
		state(int k, int r, int c)
		{
			key = k;
			row = r;
			col = c;
		}
		string str()
		{
			char buf[48];
			sprintf(buf, "%d %d %d", key, row, col);
			return string(buf);
		}
		// 就题目的数据范围来说，unsigned 可以放得下
		unsigned u32()
		{
			unsigned u = 0;
			u |= (static_cast<unsigned>(key) & USHRT_MAX) << 16;
			u |= (static_cast<unsigned>(row) & UCHAR_MAX) << 8;
			u |= (static_cast<unsigned>(col) & UCHAR_MAX) << 0;
			return u;
		}
	};

public:
	int shortestPathAllKeys(vector<string>& grid)
	{
		int rows = static_cast<int>(grid.size());
		int cols = static_cast<int>(grid[0].size());
		int x = -1, y = -1, target = -1;

		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
			{
				int c = grid[h][w];
				if (c == '@')
				{
					y = h;
					x = w;
				}
				else if ('a' <= c && c <= 'f')
					target = std::max(target, c);
			}
		target = (1 << (target - 'a' + 1)) - 1;

		int step = 0;
		int const dirs[5] = { 0, 1, 0, -1, 0 };
		state st = { 0, (char)(y), (char)(x) };
		std::vector<state> Q, R;
		unordered_set<unsigned> V;
		Q.push_back(st);
		V.insert(st.u32());

		while (!Q.empty())
		{
			++step;
			R.clear();
			for (state cur : Q)
			{
				for (int d = 0; d < 4; ++d)
				{
					st.row = cur.row + dirs[d];
					st.col = cur.col + dirs[d + 1];
					st.key = cur.key;
					if ((static_cast<unsigned>(st.row) >= static_cast<unsigned>(rows))
						|| (static_cast<unsigned>(st.col) >= static_cast<unsigned>(cols)))
						continue;
					char c = grid[st.row][st.col];
					if (c == '#')
						continue;
					if ('A' <= c && c <= 'F' && !((st.key >> (c - 'A')) & 1))
						continue;
					if ('a' <= c && c <= 'f')
						st.key |= (1 << (c - 'a'));
					if (st.key == target)
						return step;
					else if (V.insert(st.u32()).second)
						R.push_back(st);
				}
			}
			Q.swap(R);
		}

		return -1;
	}
};


int main()
{
	vector<string>
		a = { "@.a.#", "###.#", "b.A.B" },
		b = { "@..aA", "..B#.", "....b" },
		c = { "@...a", ".###A", "b.BCc" };
	Solution s;
	OutExpr(s.shortestPathAllKeys(c), "%d");
	OutExpr(s.shortestPathAllKeys(b), "%d");
	OutExpr(s.shortestPathAllKeys(a), "%d");
}
