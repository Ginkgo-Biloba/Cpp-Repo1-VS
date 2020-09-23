#include "leetcode.hpp"

/* 497. 非重叠矩形中的随机点

给定一个非重叠轴对齐矩形的列表 rects，写一个函数 pick 随机均匀地选取矩形覆盖的空间中的整数点。

提示：
		整数点是具有整数坐标的点。
		矩形周边上的点包含在矩形覆盖的空间中。
		第 i 个矩形 rects [i] = [x1，y1，x2，y2]，其中 [x1，y1] 是左下角的整数坐标，[x2，y2] 是右上角的整数坐标。
		每个矩形的长度和宽度不超过 2000。
		1 <= rects.length <= 100
		pick 以整数坐标数组 [p_x, p_y] 的形式返回一个点。
		pick 最多被调用10000次。

示例 1：
输入:
["Solution","pick","pick","pick"]
[[[[1,1,5,5]]],[],[],[]]
输出:
[null,[4,1],[4,1],[3,3]]

示例 2：
输入:
["Solution","pick","pick","pick","pick","pick"]
[[[[-2,-2,-1,-1],[1,0,3,0]]],[],[],[],[],[]]
输出:
[null,[-1,-2],[2,0],[-2,-1],[3,0],[-2,-2]]

输入语法的说明：
输入是两个列表：调用的子例程及其参数。Solution 的构造函数有一个参数，即矩形数组 rects。pick 没有参数。参数总是用列表包装的，即使没有也是如此。
*/

class Solution
{
	std::mt19937 mt;
	double ratio;
	vector<int> acml;
	vector<vector<int>> rect;

public:
	Solution(vector<vector<int>>& _rect)
		: rect(_rect)
	{
		mt.seed(time(NULL));
		acml.reserve(rect.size() + 1);
		int A = 0;
		acml.push_back(0);
		for (vector<int>& r : rect)
		{
			A += (r[2] - r[0] + 1) * (r[3] - r[1] + 1);
			acml.push_back(A);
		}
		acml.push_back(INT_MAX);
		ratio = static_cast<double>(A) / UINT_MAX;
	}

	vector<int> pick()
	{
		vector<int> p(2);
		int a = static_cast<int>(mt() * ratio);
		ptrdiff_t i = std::upper_bound(acml.begin(), acml.end(), a) - acml.begin();
		vector<int>& r = rect[i - 1];
		a = a - acml[i - 1];
		p[0] = a % (r[2] - r[0] + 1) + r[0];
		p[1] = a / (r[2] - r[0] + 1) + r[1];
		return p;
	}
};


int main()
{
	vector<vector<int>> rects =
	{
		{ -2, -2, -1, -1 },
		{ 1, 0, 3, 0 },
	};
	vector<int> p;
	Solution sln(rects);
	p = sln.pick();
	printf("%d, %d\n", p[0], p[1]);
	p = sln.pick();
	printf("%d, %d\n", p[0], p[1]);
	p = sln.pick();
	printf("%d, %d\n", p[0], p[1]);
	p = sln.pick();
	printf("%d, %d\n", p[0], p[1]);
	p = sln.pick();
	printf("%d, %d\n", p[0], p[1]);
}
