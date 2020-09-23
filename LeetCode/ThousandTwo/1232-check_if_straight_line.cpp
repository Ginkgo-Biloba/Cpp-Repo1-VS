#include "leetcode.hpp"

/* 1232. 缀点成线

在一个 XY 坐标系中有一些点，我们用数组 coordinates 来分别记录它们的坐标，其中 coordinates[i] = [x, y] 表示横坐标为 x、纵坐标为 y 的点。

请你来判断，这些点是否在该坐标系中属于同一条直线上，是则返回 true，否则请返回 false。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/10/19/untitled-diagram-2.jpg
输入：coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
输出：true

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/10/19/untitled-diagram-1.jpg
输入：coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
输出：false

提示：
	2 <= coordinates.length <= 1000
	coordinates[i].length == 2
	-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
	coordinates 中不含重复的点
*/


bool checkStraightLine(vector<vector<int>>& cd)
{
	int len = static_cast<int>(cd.size());
	int x = cd[0][0] - cd[1][0];
	int y = cd[0][1] - cd[1][1];
	for (int i = 2; i < len; ++i)
	{
		int a = cd[0][0] - cd[i][0];
		int b = cd[0][1] - cd[i][1];
		if (a * y != b * x)
			return false;
	}
	return true;
}


int main()
{}
