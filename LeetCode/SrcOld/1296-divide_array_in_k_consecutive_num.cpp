#include "leetcode.hpp"

/* 1296. 划分数组为连续数字的集合

给你一个整数数组 nums 和一个正整数 k，请你判断是否可以把这个数组划分成一些由 k 个连续数字组成的集合。
如果可以，请返回 True；否则，返回 False。

示例 1：
输入：nums = [1,2,3,3,4,4,5,6], k = 4
输出：true
解释：数组可以分成 [1,2,3,4] 和 [3,4,5,6]。

示例 2：
输入：nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
输出：true
解释：数组可以分成 [1,2,3] , [2,3,4] , [3,4,5] 和 [9,10,11]。

示例 3：
输入：nums = [3,3,2,2,1,1], k = 3
输出：true

示例 4：
输入：nums = [1,2,3,4], k = 3
输出：false
解释：数组不能分成几个大小为 3 的子数组。

提示：
	1 <= nums.length <= 10^5
	1 <= nums[i] <= 10^9
	1 <= k <= nums.length
*/

bool isPossibleDivide(vector<int>& A, int K)
{
	int len = static_cast<int>(A.size());
	if (len % K != 0)
		return false;

	vector<pair<int, int>> M;
	sort(A.begin(), A.end());
	for (int h = 0; h < len;)
	{
		int i = h + 1;
		while ((i < len) && (A[h] == A[i]))
			++i;
		M.emplace_back(A[h], i - h);
		h = i;
	}

	len = static_cast<int>(M.size());
	if (len < K)
		return false;
	for (int h = 0; h < len; ++h)
		if (M[h].second)
		{
			int need = M[h].second;
			int i = h + K - 1;
			if (i > len)
				return false;
			for (; i >= h; --i)
			{
				if ((M[i].second < need)
					|| (M[i].first != i - h + M[h].first))
					return false;
				M[i].second -= need;
			}
		}
	return true;
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 3, 4, 4, 5, 6 },
		b = { 3, 2, 1, 2, 3, 4, 3, 4, 5, 9, 10, 11 },
		c = { 3, 3, 2, 2, 1, 1 },
		d = { 1, 2, 3, 4 };
	OutBool(isPossibleDivide(a, 4));
	OutBool(isPossibleDivide(b, 3));
	OutBool(isPossibleDivide(c, 3));
	OutBool(isPossibleDivide(d, 3));
}
