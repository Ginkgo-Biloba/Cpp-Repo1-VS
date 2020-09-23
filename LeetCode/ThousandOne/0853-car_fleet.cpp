#include "leetcode.hpp"

/* 853. 车队

N 辆车沿着一条车道驶向位于 target 英里之外的共同目的地。

每辆车 i 以恒定的速度 speed[i] （英里/小时），从初始位置 position[i]（英里）沿车道驶向目的地。

一辆车永远不会超过前面的另一辆车，但它可以追上去，并与前车以相同的速度紧接着行驶。

此时，我们会忽略这两辆车之间的距离，也就是说，它们被假定处于相同的位置。

车队 是一些由行驶在相同位置、具有相同速度的车组成的非空集合。注意，一辆车也可以是一个车队。

即便一辆车在目的地才赶上了一个车队，它们仍然会被视作是同一个车队。

会有多少车队到达目的地?

示例：
输入：target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
输出：3
解释：
从 10 和 8 开始的车会组成一个车队，它们在 12 处相遇。
从 0 处开始的车无法追上其它车，所以它自己就是一个车队。
从 5 和 3 开始的车会组成一个车队，它们在 6 处相遇。
请注意，在到达目的地之前没有其它车会遇到这些车队，所以答案是 3。

提示：
	0 <= N <= 10 ^ 4
	0 < target <= 10 ^ 6
	0 < speed[i] <= 10 ^ 6
	0 <= position[i] < target
	所有车的初始位置各不相同。
*/

int carFleet(int target, vector<int>& position, vector<int>& speed)
{
	int ans = 0;
	int N = static_cast<int>(speed.size());
	double cur = target;
	vector<pair<double, double>> car;
	car.reserve(N);
	for (int i = 0; i < N; ++i)
		car.emplace_back(position[i], (cur - position[i]) / speed[i]);

	sort(car.begin(), car.end());
	cur = 0;
	for (int i = N - 1; i >= 0; --i)
		if (car[i].second > cur)
		{
			cur = car[i].second;
			++ans;
		}

	return ans;
}

int main()
{
	vector<int>
		p = { 10, 8, 0, 5, 3 },
		s = { 2, 4, 1, 1, 3 };
	OutExpr(carFleet(12, p, s), "%d");
}
