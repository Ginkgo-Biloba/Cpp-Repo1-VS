#include "leetcode.hpp"

/* 1575. 统计所有可行路径

给你一个 互不相同 的整数数组，其中 locations[i] 表示第 i 个城市的位置。
同时给你 start，finish 和 fuel 分别表示出发城市、目的地城市和你初始拥有的汽油总量

每一步中，如果你在城市 i ，你可以选择任意一个城市 j ，满足  j != i 且 0 <= j < locations.length ，并移动到城市 j 。从城市 i 移动到 j 消耗的汽油量为 |locations[i] - locations[j]|，|x| 表示 x 的绝对值。

请注意， fuel 任何时刻都 不能 为负，且你 可以 经过任意城市超过一次（包括 start 和 finish ）。

请你返回从 start 到 finish 所有可能路径的数目。

由于答案可能很大，请将它对 10^9 + 7 取余后返回。

示例 1：
输入：locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
输出：4
解释：以下为所有可能路径，每一条都用了 5 单位的汽油：
1 -> 3
1 -> 2 -> 3
1 -> 4 -> 3
1 -> 4 -> 2 -> 3

示例 2：
输入：locations = [4,3,1], start = 1, finish = 0, fuel = 6
输出：5
解释：以下为所有可能的路径：
1 -> 0，使用汽油量为 fuel = 1
1 -> 2 -> 0，使用汽油量为 fuel = 5
1 -> 2 -> 1 -> 0，使用汽油量为 fuel = 5
1 -> 0 -> 1 -> 0，使用汽油量为 fuel = 3
1 -> 0 -> 1 -> 0 -> 1 -> 0，使用汽油量为 fuel = 5

示例 3：
输入：locations = [5,2,1], start = 0, finish = 2, fuel = 3
输出：0
解释：没有办法只用 3 单位的汽油从 0 到达 2 。因为最短路径需要 4 单位的汽油。

示例 4 ：
输入：locations = [2,1,5], start = 0, finish = 0, fuel = 3
输出：2
解释：总共有两条可行路径，0 和 0 -> 1 -> 0 。

示例 5：
输入：locations = [1,2,3], start = 0, finish = 2, fuel = 40
输出：615088286
解释：路径总数为 2615088300 。将结果对 10^9 + 7 取余，得到 615088286 。

提示：
	2 <= locations.length <= 100
	1 <= locations[i] <= 10^9
	所有 locations 中的整数 互不相同 。
	0 <= start, finish < locations.length
	1 <= fuel <= 200
*/

class Solution
{
	vector<array<int, 201>> buffer;
	vector<vector<array<int, 2>>> reach;
	int numloc, idxstop;

	int dp(int idx, int fuel)
	{
		int const mod = 1e9 + 7;
		int* ptr = buffer[idx].data() + fuel;
		if (*ptr >= 0)
			return *ptr;
		int val = (idx == idxstop);
		auto& dest = reach[idx];
		for (auto& dk : dest)
		{
			int rest = fuel - dk[0];
			if (rest < 0)
				break;
			val = (val + dp(dk[1], rest)) % mod;
		}
		return (*ptr = val);
	}

public:
	int countRoutes(vector<int>& loc, int start, int finish, int fuel)
	{
		numloc = static_cast<int>(loc.size());
		idxstop = finish;
		reach.resize(numloc);
		for (int i = 0; i < numloc; ++i)
		{
			reach[i].clear();
			for (int k = 0; k < numloc; ++k)
			{
				int d = abs(loc[i] - loc[k]);
				if ((i != k) && (d <= fuel))
					reach[i].push_back({ d, k });
			}
			sort(reach[i].begin(), reach[i].end(),
				[](array<int, 2> const& a, array<int, 2> const& b) -> bool { return a[0] < b[0]; });
		}
		buffer.resize(numloc + 1);
		memset(buffer.data(), 0xff, buffer.size() * sizeof(buffer[0]));
		dp(start, fuel);
		return buffer[start][fuel];
	}
};


int main()
{
	vector<int>
		a = { 2, 3, 6, 8, 4 },
		b = { 4, 3, 1 },
		c = { 5, 2, 1 },
		d = { 2, 1, 5 },
		e = { 1, 2, 3 };
	Solution s;
	OutExpr(s.countRoutes(a, 1, 3, 5), "%d");
	OutExpr(s.countRoutes(b, 1, 0, 6), "%d");
	OutExpr(s.countRoutes(c, 0, 2, 3), "%d");
	OutExpr(s.countRoutes(d, 0, 0, 3), "%d");
	OutExpr(s.countRoutes(e, 0, 2, 40), "%d");
}
