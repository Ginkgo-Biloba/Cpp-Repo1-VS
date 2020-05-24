#include "leetcode.hpp"

/* 219. 存在重复元素 II

给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]，并且 i 和 j 的差的 绝对值 至多为 k。

示例 1:
输入: nums = [1,2,3,1], k = 3
输出: true

示例 2:
输入: nums = [1,0,1,1], k = 1
输出: true

示例 3:
输入: nums = [1,2,3,1,2,3], k = 2
输出: false
*/

bool containsNearbyDuplicate(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	unordered_map<int, int> M;
	for (int i = 0; i < len; ++i)
	{
		auto it = M.emplace(A[i], i);
		if (!(it.second))
		{
			if (i - it.first->second <= k)
				return true;
			it.first->second = i;
		}
	}
	return false;
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 1 },
		b = { 1, 0, 1, 1 },
		c = { 1, 2, 3, 1, 2, 3 };
	OutBool(containsNearbyDuplicate(a, 3));
	OutBool(containsNearbyDuplicate(b, 1));
	OutBool(containsNearbyDuplicate(c, 2));
}
