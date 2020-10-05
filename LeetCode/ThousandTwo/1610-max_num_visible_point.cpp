#include "leetcode.hpp"

/* 1610. 可见点的最大数目

给你一个点数组 points 和一个表示角度的整数 angle ，你的位置是 location ，其中 location = [posx, posy] 且 points[i] = [xi, yi] 都表示 X-Y 平面上的整数坐标。

最开始，你面向东方进行观测。
你 不能 进行移动改变位置，但可以通过 自转 调整观测角度。
换句话说，posx 和 posy 不能改变。你的视野范围的角度用 angle 表示， 这决定了你观测任意方向时可以多宽。
设 d 为逆时针旋转的度数，那么你的视野就是角度范围 [d - angle/2, d + angle/2] 所指示的那片区域。

https://assets.leetcode.com/uploads/2020/09/30/angle.mp4
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/angle.mp4

对于每个点，如果由该点、你的位置以及从你的位置直接向东的方向形成的角度 位于你的视野中 ，那么你就可以看到它。

同一个坐标上可以有多个点。
你所在的位置也可能存在一些点，但不管你的怎么旋转，总是可以看到这些点。
同时，点不会阻碍你看到其他点。

返回你能看到的点的最大数目。

示例 1：
https://assets.leetcode.com/uploads/2020/09/30/89a07e9b-00ab-4967-976a-c723b2aa8656.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/89a07e9b-00ab-4967-976a-c723b2aa8656.png
输入：points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
输出：3
解释：阴影区域代表你的视野。
在你的视野中，所有的点都清晰可见，尽管 [2,2] 和 [3,3]在同一条直线上，你仍然可以看到 [3,3] 。

示例 2：
输入：points = [[2,1],[2,2],[3,4],[1,1]], angle = 90, location = [1,1]
输出：4
解释：在你的视野中，所有的点都清晰可见，包括你所在位置的那个点。

示例 3：
https://assets.leetcode.com/uploads/2020/09/30/5010bfd3-86e6-465f-ac64-e9df941d2e49.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/10/04/5010bfd3-86e6-465f-ac64-e9df941d2e49.png
输入：points = [[0,1],[2,1]], angle = 13, location = [1,1]
输出：1
解释：如图所示，你只能看到两点之一。

提示：
	1 <= points.length <= 10^5
	points[i].length == 2
	location.length == 2
	0 <= angle < 360
	0 <= posx, posy, xi, yi <= 10^9
*/


// 抄的第 18 名 DickLearning 的
int visiblePoints(
	vector<vector<int>>& points, int angle, vector<int>& location)
{
	int len = static_cast<int>(points.size());
	vector<double> A;
	int org = 0, ans = 0;
	for (int i = 0; i < len; ++i)
	{
		int x = points[i][0] - location[0];
		int y = points[i][1] - location[1];
		if (x == 0 && y == 0)
			++org;
		else
			A.push_back(atan2(1.0 * y, 1.0 * x));
	}

	// 这个 pi 需要算出来
	double pi = acos(-1.0);
	double dif = angle / 180.0 * pi;
	int i, k = 0;
	sort(A.begin(), A.end());
	len = static_cast<int>(A.size());
	for (i = 0; i < len; ++i)
		A.push_back(A[i] + 2.0 * pi);
	for (i = 0; i < len; ++i)
	{
		while ((k < i + len) && (A[k] - A[i] <= dif))
			++k;
		ans = max(k - i, ans);
	}
	return ans + org;
}


int main()
{}
