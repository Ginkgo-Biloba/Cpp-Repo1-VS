#include "leetcode.hpp"
#include <random>

/* 384. 打乱数组

打乱一个没有重复元素的数组。

示例:

// 以数字集合 1, 2 和 3 初始化数组。
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。
solution.shuffle();

// 重设数组到它的初始状态[1,2,3]。
solution.reset();

// 随机返回数组[1,2,3]打乱后的结果。
solution.shuffle();
*/

class Solution
{
	vector<int> ary;
	int len;
	std::mt19937 mt;

public:
	Solution(vector<int>& nums)
		: ary(nums)
	{
		len = static_cast<int>(ary.size());
		std::random_device rd;
		mt.seed(rd());
	}

	/** Resets the array to its original configuration and return it. */
	vector<int> reset()
	{
		return ary;
	}

	/** Returns a random shuffling of the array. */
	vector<int> shuffle()
	{
		if (len < 1)
			return ary;

		// Fisher–Yates shuffle 洗牌算法
		// https://gaohaoyang.github.io/2016/10/16/shuffle-algorithm/
		vector<int> cur = ary;
		for (int t = len; --t;)
		{
			int i = mt() % (t + 1);
			std::swap(cur[t], cur[i]);
		}
		return cur;
	}
};


int main()
{
	vector<int> nums = { 1, 2, 3, 4 };
	Solution* obj = new Solution(nums);
	output(obj->shuffle(), "shuffle");
	output(obj->reset(), "reset");
	delete obj;
}
