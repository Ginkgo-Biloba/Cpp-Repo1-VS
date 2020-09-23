#include "leetcode.hpp"

/* 850. 矩形面积 II

我们给出了一个（轴对齐的）矩形列表 rectangles。
对于 rectangle[i] = [x1, y1, x2, y2]，其中（x1，y1）是矩形 i 左下角的坐标，（x2，y2）是该矩形右上角的坐标。

找出平面中所有矩形叠加覆盖后的总面积。 由于答案可能太大，请返回它对 10 ^ 9 + 7 取模的结果。

示例 1：
输入：[[0,0,2,2],[1,0,2,3],[1,0,3,1]]
输出：6
解释：如图所示。
https://s3-lc-upload.s3.amazonaws.com/uploads/2018/06/06/rectangle_area_ii_pic.png

示例 2：
输入：[[0,0,1000000000,1000000000]]
输出：49
解释：答案是 10^18 对 (10^9 + 7) 取模的结果，即 (10^9)^2 → (-7)^2 = 49 。

提示：
	1 <= rectangles.length <= 200
	rectanges[i].length = 4
	0 <= rectangles[i][j] <= 10^9
	矩形叠加覆盖后的总面积不会超越 2^63 - 1，这意味着可以用一个 64 位有符号整数来保存面积结果。
*/

// https://leetcode.com/problems/rectangle-area-ii/discuss/137914/C%2B%2BPython-Discretization-and-O(NlogN)
// 抄的
int rectangleArea(vector<vector<int>>& rect)
{
	int64_t const Mod = 1e9 + 7;

	vector<int> X;
	X.push_back(0);
	for (auto r : rect)
	{
		X.push_back(r[0]);
		X.push_back(r[2]);
	}

	sort(X.begin(), X.end());
	auto uend = unique(X.begin(), X.end());
	X.erase(uend, X.end());

	int len = static_cast<int>(X.size());
	unordered_map<int, int> XI;
	for (int i = 0; i < len; ++i)
		XI[X[i]] = i;

	vector<int> count(len);
	vector<vector<int>> L;
	for (auto r : rect)
	{
		int x1 = r[0], y1 = r[1], x2 = r[2], y2 = r[3];
		L.push_back({ y1, x1, x2, 1 });
		L.push_back({ y2, x1, x2, -1 });
	}

	sort(L.begin(), L.end());
	int64_t cury = 0, curx_sum = 0, area = 0;
	for (auto const& l : L)
	{
		int64_t y = l[0];
		int x1 = l[1], x2 = l[2];
		area = (area + (y - cury) * curx_sum) % Mod;
		cury = y;
		for (int i = XI[x1]; i < XI[x2]; ++i)
			count[i] += l[3];
		curx_sum = 0;
		for (int i = 0; i < len; ++i)
		{
			if (count[i] > 0)
				curx_sum += X[i + 1] - X[i];
		}
	}

	return static_cast<int>(area);
}

int main()
{
	vector<vector<int>>
		a = { { 0, 0, 2, 2 }, { 1, 0, 2, 3 }, { 1, 0, 3, 1 } },
		b = { { 0, 0, 1000000000, 1000000000 } };
	OutExpr(rectangleArea(a), "%d");
	OutExpr(rectangleArea(b), "%d");
}
