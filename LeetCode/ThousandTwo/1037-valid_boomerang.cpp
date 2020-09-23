#include "leetcode.hpp"

/* 1037. 有效的回旋镖

回旋镖定义为一组三个点，这些点各不相同且不在一条直线上。

给出平面上三个点组成的列表，判断这些点是否可以构成回旋镖。

示例 1：
输入：[[1,1],[2,3],[3,2]]
输出：true

示例 2：
输入：[[1,1],[2,2],[3,3]]
输出：false

提示：
	points.length == 3
	points[i].length == 2
	0 <= points[i][j] <= 100
*/

bool isBoomerang(vector<vector<int>>& points)
{
	int ax = points[1][0] - points[0][0];
	int ay = points[1][1] - points[0][1];
	int bx = points[2][0] - points[0][0];
	int by = points[2][1] - points[0][1];
	return ax * by != ay * bx;
}

int main()
{
	vector<vector<int>>
		a = { { 1, 1 }, { 2, 3 }, { 3, 2 } },
		b = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
	OutBool(isBoomerang(a));
	OutBool(isBoomerang(b));
}
