#include "leetcode.hpp"

/* 473. 火柴拼正方形

还记得童话《卖火柴的小女孩》吗？现在，你知道小女孩有多少根火柴，请找出一种能使用所有火柴拼成一个正方形的方法。
不能折断火柴，可以把火柴连接起来，并且每根火柴都要用到。

输入为小女孩拥有火柴的数目，每根火柴用其长度表示。输出即为是否能用所有的火柴拼成正方形。

示例 1:
输入: [1,1,2,2,2]
输出: true
解释: 能拼成一个边长为2的正方形，每边两根火柴。

示例 2:
输入: [3,3,3,3,4]
输出: false
解释: 不能用所有火柴拼成一个正方形。

注意:
给定的火柴长度和在 0 到 10^9之间。
火柴数组的长度不超过15。
*/

// https://leetcode.com/problems/matchsticks-to-square/discuss/95744/cpp-6ms-solution-with-DFS
// 抄的
class Solution
{
	int* ptr;
	int len;
	unsigned side[4];
	unsigned target;

	bool dfs(int idx)
	{
		if (idx == len)
			return side[0] == side[1] && side[0] == side[2] && side[0] == side[3];
		for (int i = 0; i < 4; ++i)
		{
			if (side[i] + ptr[idx] > target)
				continue;
			int k = i - 1;
			for (; k >= 0; --k)
			{
				if (side[k] == side[i])
					break;
			}
			if (k != -1)
				continue;
			side[i] += ptr[idx];
			if (dfs(idx + 1))
				return true;
			side[i] -= ptr[idx];
		}
		return false;
	}

public:
	bool makesquare(vector<int>& nums)
	{
		len = static_cast<int>(nums.size());
		if (len < 4)
			return false;
		ptr = nums.data();
		std::sort(nums.begin(), nums.end(), std::greater<int>());
		ptr = nums.data();
		int64_t sum = nums[0];
		for (int i = 1; i < len; ++i)
			sum += ptr[i];
		if (sum % 4 != 0)
			return false;
		memset(side, 0, sizeof(side));
		target = static_cast<unsigned>(sum / 4);
		return dfs(0);
	}
};


int main()
{
	vector<int> nums = { 1, 1, 2, 2, 2 };
	OutExpr(boolstr[Solution().makesquare(nums)], "%s");
}
