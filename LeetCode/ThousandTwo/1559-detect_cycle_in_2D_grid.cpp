#include "leetcode.hpp"

/* 1559. 二维网格图中探测环

给你一个二维字符网格数组 grid ，大小为 m x n ，你需要检查 grid 中是否存在 相同值 形成的环。

一个环是一条开始和结束于同一个格子的长度 大于等于 4 的路径。
对于一个给定的格子，你可以移动到它上、下、左、右四个方向相邻的格子之一，可以移动的前提是这两个格子有 相同的值 。

同时，你也不能回到上一次移动时所在的格子。
比方说，环  (1, 1) -> (1, 2) -> (1, 1) 是不合法的，因为从 (1, 2) 移动到 (1, 1) 回到了上一次移动时的格子。

如果 grid 中有相同值形成的环，请你返回 true，否则返回 false。

示例 1：
https://assets.leetcode.com/uploads/2020/07/15/1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/22/5482e1.png
输入：grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
输出：true
解释：如下图所示，有 2 个用不同颜色标出来的环：
https://assets.leetcode.com/uploads/2020/07/15/11.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/22/5482e11.png

示例 2：
https://assets.leetcode.com/uploads/2020/07/15/22.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/22/5482e2.png
输入：grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
输出：true
解释：如下图所示，只有高亮所示的一个合法环：
https://assets.leetcode.com/uploads/2020/07/15/2.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/22/5482e22.png

示例 3：
https://assets.leetcode.com/uploads/2020/07/15/3.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/22/5482e3.png
输入：grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
输出：false

提示：
	m == grid.length
	n == grid[i].length
	1 <= m <= 500
	1 <= n <= 500
	grid 只包含小写英文字母。
*/

class Solution
{
	int rows, cols;
	vector<array<int, 2>> curr, temp;
	vector<vector<char>> grid;

	bool bfs(int h, int w)
	{
		int const dir[] = { -1, 0, 1, 0, -1 };
		unsigned height = rows, width = cols;
		char val = grid[h][w];
		curr.clear();
		curr.push_back({ h, w });
		grid[h][w] = '1';
		while (!(curr.empty()))
		{
			temp.clear();
			for (auto& p : curr)
				for (int d = 0; d < 4; ++d)
				{
					h = p[0] + dir[d];
					w = p[1] + dir[d + 1];
					if (static_cast<unsigned>(h) >= height
						|| static_cast<unsigned>(w) >= width)
						continue;
					char alnum = grid[h][w];
					if (alnum == '0')
						return true;
					if (alnum != val)
						continue;
					grid[h][w] = '0';
					temp.push_back({ h, w });
				}
			for (auto& p : temp)
				grid[p[0]][p[1]] = '1';
			temp.swap(curr);
		}
		return false;
	}

public:
	bool containsCycle(vector<vector<char>>& _grid)
	{
		grid.swap(_grid);
		rows = static_cast<int>(grid.size());
		cols = static_cast<int>(grid[0].size());
		if (rows < 2 || cols < 2)
			return false;
		for (int h = 0; h < rows; ++h)
			for (int w = 0; w < cols; ++w)
				if (isalpha(grid[h][w]))
				{
					bool cur = bfs(h, w);
					if (cur)
						return true;
				}
		return false;
	}
};

int main()
{
	vector<vector<char>>
		a = {
			{ 'a', 'a', 'a', 'a' },
			{ 'a', 'b', 'b', 'a' },
			{ 'a', 'b', 'b', 'a' },
			{ 'a', 'a', 'a', 'a' },
	},
	b = {
		{ 'c', 'c', 'c', 'a' },
		{ 'c', 'd', 'c', 'c' },
		{ 'c', 'c', 'e', 'c' },
		{ 'f', 'c', 'c', 'c' },
	},
	c = {
		{ 'a', 'b', 'b' },
		{ 'b', 'z', 'b' },
		{ 'b', 'b', 'a' },
	};
	Solution s;
	OutBool(s.containsCycle(a));
	OutBool(s.containsCycle(b));
	OutBool(s.containsCycle(c));
}
