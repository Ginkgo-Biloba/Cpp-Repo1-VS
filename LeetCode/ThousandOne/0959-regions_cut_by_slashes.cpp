#include "leetcode.hpp"

/* 959. 由斜杠划分区域

在由 1 x 1 方格组成的 N x N 网格 grid 中，每个 1 x 1 方块由 /、\ 或空格构成。
这些字符会将方块划分为一些共边的区域。

请注意，反斜杠字符是转义的，因此 \ 用 "\\" 表示。

返回区域的数目。

示例 1：
输入：
[
	" /",
	"/ "
]
输出：2
解释：2x2 网格如下：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/15/1.png

示例 2：
输入：
[
	" /",
	"  "
]
输出：1
解释：2x2 网格如下：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/15/2.png

示例 3：
输入：
[
	"\\/",
	"/\\"
]
输出：4
解释：（回想一下，因为 \ 字符是转义的，所以 "\\/" 表示 \/，而 "/\\" 表示 /\。）
2x2 网格如下：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/15/3.png

示例 4：
输入：
[
	"/\\",
	"\\/"
]
输出：5
解释：（回想一下，因为 \ 字符是转义的，所以 "/\\" 表示 /\，而 "\\/" 表示 \/。）
2x2 网格如下：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/15/4.png

示例 5：
输入：
[
	"//",
	"/ "
]
输出：3
解释：2x2 网格如下：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/15/5.png

提示：
	1 <= grid.length == grid[0].length <= 30
	grid[i][j] 是 '/'、'\'、或 ' '。
*/

// https://leetcode.com/problems/regions-cut-by-slashes/discuss/205674/C%2B%2B-with-picture-DFS-on-upscaled-grid
// 抄的
int regionsBySlashes(vector<string>& grid)
{
	int const dirs[] = { -1, 0, 1, 0, -1 };
	int n = static_cast<int>(grid.size());
	int n3 = n * 3, count = 0;
	unsigned un3 = n3;
	vector<char> g3(n3 * n3);
	auto at = [n3](int y, int x) { return y * n3 + x; };
	vector<pair<short, short>> cur, nxt;

	// 画画
	for (int h = 0; h < n; ++h)
		for (int w = 0; w < n; ++w)
		{
			int h3 = h * 3, w3 = w * 3;
			if (grid[h][w] == '\\')
			{
				g3[at(h3 + 0, w3 + 0)] = -1;
				g3[at(h3 + 1, w3 + 1)] = -1;
				g3[at(h3 + 2, w3 + 2)] = -1;
			}
			else if (grid[h][w] == '/')
			{
				g3[at(h3 + 0, w3 + 2)] = -1;
				g3[at(h3 + 1, w3 + 1)] = -1;
				g3[at(h3 + 2, w3 + 0)] = -1;
			}
		}

	// 广搜
	for (int h = 0; h < n3; ++h)
		for (int w = 0; w < n3; ++w)
		{
			if (g3[at(h, w)] != 0)
				continue;
			++count;
			cur.emplace_back((short)(h), (short)(w));
			g3[at(h, w)] = 1;
			while (!cur.empty())
			{
				nxt.clear();
				for (auto it : cur)
					for (int d = 0; d < 4; ++d)
					{
						int dy = it.first + dirs[d];
						int dx = it.second + dirs[d + 1];
						if (static_cast<unsigned>(dy) >= un3
							|| static_cast<unsigned>(dx) >= un3
							|| g3[at(dy, dx)] != 0)
							continue;
						nxt.emplace_back((short)(dy), (short)(dx));
						g3[at(dy, dx)] = 1;
					}
				nxt.swap(cur);
			}
		}

	return count;
}


int main()
{
	vector<string>
		a = { " /", "/ " },
		b = { " /", "  " },
		c = { "\\/", "/\\" },
		d = { "/\\", "\\/" },
		e = { "//", "/ " };
	OutExpr(regionsBySlashes(a), "%d");
	OutExpr(regionsBySlashes(b), "%d");
	OutExpr(regionsBySlashes(c), "%d");
	OutExpr(regionsBySlashes(d), "%d");
	OutExpr(regionsBySlashes(e), "%d");
}
