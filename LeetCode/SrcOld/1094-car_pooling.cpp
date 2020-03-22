#include "leetcode.hpp"

/* 1094. 拼车

假设你是一位顺风车司机，车上最初有 capacity 个空座位可以用来载客。
由于道路的限制，车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向，你可以将其想象为一个向量）。

这儿有一份行程计划表 trips[][]，其中 trips[i] = [num_passengers, start_location, end_location] 包含了你的第 i 次行程信息：
	必须接送的乘客数量；
	乘客的上车地点；
	以及乘客的下车地点。

这些给出的地点位置是从你的 初始 出发位置向前行驶到这些地点所需的距离（它们一定在你的行驶方向上）。

请你根据给出的行程计划表和车子的座位数，来判断你的车是否可以顺利完成接送所用乘客的任务。
当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。
*/

class Solution
{
public:
	bool carPooling(vector<vector<int>>& trips, int capacity)
	{
		int num = 0;
		vector<pair<int, int>> vary;
		for (auto const& t : trips)
		{
			vary.emplace_back(t[1], t[0]);
			vary.emplace_back(t[2], -t[0]);
		}
		sort(vary.begin(), vary.end());
		for (auto const& v : vary)
		{
			num = max(num + v.second, 0);
			if (num > capacity)
				return false;
		}
		return true;
	}
};

int main()
{}
