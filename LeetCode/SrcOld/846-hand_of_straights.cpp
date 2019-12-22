#include "leetcode.hpp"

/* 846. 一手顺子

爱丽丝有一手（hand）由整数数组给定的牌。
现在她想把牌重新排列成组，使得每个组的大小都是 W，且由 W 张连续的牌组成。
如果她可以完成分组就返回 true，否则返回 false。

示例 1：
输入：hand = [1,2,3,6,2,3,4,7,8], W = 3
输出：true
解释：爱丽丝的手牌可以被重新排列为 [1,2,3]，[2,3,4]，[6,7,8]。

示例 2：
输入：hand = [1,2,3,4,5], W = 4
输出：false
解释：爱丽丝的手牌无法被重新排列成几个大小为 4 的组。

提示：
	1 <= hand.length <= 10000
	0 <= hand[i] <= 10^9
	1 <= W <= hand.length
*/

// https://leetcode.com/problems/hand-of-straights/discuss/135598/C%2B%2BJavaPython-O(MlogM)-Complexity
// 抄的
bool isNStraightHand(vector<int>& hand, int W)
{
	std::map<int, int> count;
	// 以它为起点，截至目前需要那么多个数字
	// std::deque<int> start;
	vector<int> start;
	size_t idx = 0, szW = W;
	pair<int, int> last;
	if (W == 0 || (static_cast<int>(hand.size()) % W))
		return false;

	for (int h : hand)
		++(count[h]);

	start.reserve(count.size());
	for (auto it : count)
	{
		// 如果不连续，或者数量不够
		if (((last.second > 0) && (it.first > last.first + 1))
			|| (it.second < last.second))
			return false;
		// 需要 push_back(0) 保证 start.size() == W
		start.push_back(it.second - last.second);
		last = it;
		if (start.size() == idx + szW)
		{
			last.second -= start[idx];
			++idx;
		}
	}

	return last.second == 0;
}

int main()
{
	vector<int>
		a = { 1, 2, 3, 6, 2, 3, 4, 7, 8 },
		b = { 1, 2, 3, 4, 5 };
	OutBool(isNStraightHand(a, 3));
	OutBool(isNStraightHand(b, 4));
}
