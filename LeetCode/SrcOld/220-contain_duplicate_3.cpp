#include "leetcode.hpp"

/* 220. 存在重复元素 III

给定一个整数数组，判断数组中是否有两个不同的索引 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值最大为 t，并且 i 和 j 之间的差的绝对值最大为 ķ。

示例 1:
输入: nums = [1,2,3,1], k = 3, t = 0
输出: true

示例 2:
输入: nums = [1,0,1,1], k = 1, t = 2
输出: true

示例 3:
输入: nums = [1,5,9,1,5,9], k = 2, t = 3
输出: false
*/

bool containsNearbyAlmostDuplicate(vector<int>& A, int k, int t)
{
	int len = static_cast<int>(A.size());
	if (len < 2)
		return false;
	int64_t tq = t;
	set<int64_t> S;
	for (int i = 0; i < len; ++i)
	{
		if (i > k)
			S.erase(A[i - k - 1]);
		auto it = S.lower_bound(A[i] - tq);
		if ((it != S.end()) && ((*it) - A[i] <= tq))
			return true;
		S.insert(A[i]);
	}
	return false;
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 1 },
		b = { 1, 0, 1, 1 },
		c = { 1, 5, 9, 1, 5, 9 };
	OutBool(containsNearbyAlmostDuplicate(a, 3, 0));
	OutBool(containsNearbyAlmostDuplicate(b, 1, 2));
	OutBool(containsNearbyAlmostDuplicate(c, 2, 3));
}
