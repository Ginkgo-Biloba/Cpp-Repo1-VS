#include "leetcode.hpp"

/* 1349. 参加考试的最大学生数

给你一个 m * n 的矩阵 seats 表示教室中的座位分布。
如果座位是坏的（不可用），就用 '#' 表示；否则，用 '.' 表示。

学生可以看到左侧、右侧、左上、右上这四个方向上紧邻他的学生的答卷，但是看不到直接坐在他前面或者后面的学生的答卷。
请你计算并返回该考场可以容纳的一起参加考试且无法作弊的最大学生人数。

学生必须坐在状况良好的座位上。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/02/09/image.png
输入：seats = [
	["#",".","#","#",".","#"],
	[".","#","#","#","#","."],
	["#",".","#","#",".","#"]
]
输出：4
解释：教师可以让 4 个学生坐在可用的座位上，这样他们就无法在考试中作弊。

示例 2：

输入：seats = [
	[".","#"],
	["#","#"],
	["#","."],
	["#","#"],
	[".","#"]
]
输出：3
解释：让所有学生坐在可用的座位上。

示例 3：

输入：seats = [
	["#",".",".",".","#"],
	[".","#",".","#","."],
	[".",".","#",".","."],
	[".","#",".","#","."],
	["#",".",".",".","#"]
]
输出：10
解释：让学生坐在第 1、3 和 5 列的可用座位上。



提示：
	seats 只包含字符 '.' 和'#'
	m == seats.length
	n == seats[i].length
	1 <= m <= 8
	1 <= n <= 8
*/

int popcnt(uint32_t v)
{
	v = (v & UINT32_C(0x55555555)) + ((v >> 1) & UINT32_C(0x55555555));
	v = (v & UINT32_C(0x33333333)) + ((v >> 2) & UINT32_C(0x33333333));
	v = (v & UINT32_C(0x0f0f0f0f)) + ((v >> 4) & UINT32_C(0x0f0f0f0f));
	v = (v & UINT32_C(0x00ff00ff)) + ((v >> 8) & UINT32_C(0x00ff00ff));
	v = (v & UINT32_C(0x0000ffff)) + ((v >> 16) & UINT32_C(0x0000ffff));
	return static_cast<int>(v);
}

// https://leetcode.com/problems/maximum-students-taking-exam/discuss/503686/A-simple-tutorial-on-this-bitmasking-problem
// 抄的
int maxStudents(vector<vector<char>>& seats)
{
	int rows = static_cast<int>(seats.size());
	int cols = static_cast<int>(seats[0].size());
	vector<int> valid(rows);
	for (int h = 0; h < rows; ++h)
	{
		int cur = 0;
		char const* S = seats[h].data();
		for (int w = 0; w < cols; ++w)
			cur = (cur << 1) | (S[w] == '.');
		valid[h] = cur;
	}

	int numstate = 1 << cols;
	vector<int> buffer((rows + 1) * numstate, -1);
	auto F = [&buffer, numstate](int h, int s) -> int&
	{
		return buffer[h * numstate + s];
	};

	// think of a virtual row in the front and no students are sitting in that row
	F(0, 0) = 0;
	for (int h = 1; h <= rows; ++h)
	{
		int cur = valid[h - 1];
		for (int s = 0; s < numstate; ++s)
			if ((s & cur) == s && !(s & (s >> 1)))
			{
				for (int k = 0; k < numstate; ++k)
					if (F(h - 1, k) != -1
						&& !(s & (k >> 1))
						&& !((s >> 1) & k))
					{
						F(h, s) = max(F(h, s),
							F(h - 1, k) + popcnt(s));
					}
			}
	}

	int ans = 0;
	for (int s = 0; s < numstate; ++s)
		ans = max(ans, F(rows, s));
	return ans;
}


int main()
{
	vector<vector<char>>
		a = {
			{ '#', '.', '#', '#', '.', '#' },
			{ '.', '#', '#', '#', '#', '.' },
			{ '#', '.', '#', '#', '.', '#' },
	},
	b = {
		{ '.', '#' },
		{ '#', '#' },
		{ '#', '.' },
		{ '#', '#' },
		{ '.', '#' },
	},
	c = {
		{ '#', '.', '.', '.', '#' },
		{ '.', '#', '.', '#', '.' },
		{ '.', '.', '#', '.', '.' },
		{ '.', '#', '.', '#', '.' },
		{ '#', '.', '.', '.', '#' },
	};
	OutExpr(maxStudents(a), "%d");
	OutExpr(maxStudents(b), "%d");
	OutExpr(maxStudents(c), "%d");
}
