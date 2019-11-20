#include "leetcode.hpp"

/* 673. 最长递增子序列的个数

给定一个未排序的整数数组，找到最长递增子序列的个数。

示例 1:
输入: [1,3,5,4,7]
输出: 2
解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。

示例 2:
输入: [2,2,2,2,2]
输出: 5
解释: 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。

注意: 给定的数组长度不超过 2000 并且结果一定是32位有符号整数。
*/

int findNumberOfLIS(vector<int> const& nums)
{
	int N = static_cast<int>(nums.size());
	int maxlen = 0, maxcnt = 0;
	vector<int> len(N, 1), cnt(N, 1);
	for (int R = 0; R < N; ++R)
	{
		for (int L = 0; L < R; ++L)
			if (nums[L] < nums[R])
			{
				if (len[L] + 1 == len[R])
					cnt[R] += cnt[L];
				else if (len[L] + 1 > len[R])
				{
					len[R] = len[L] + 1;
					cnt[R] = cnt[L];
				}
			}
		if (maxlen == len[R])
			maxcnt += cnt[R];
		else if (maxlen < len[R])
		{
			maxlen = len[R];
			maxcnt = cnt[R];
		}
	}
	return maxcnt;
}


int main()
{
	OutExpr(findNumberOfLIS({ 1, 3, 5, 4, 7 }), "%d");
	OutExpr(findNumberOfLIS({ 2, 2, 2, 2, 2 }), "%d");
	OutExpr(findNumberOfLIS({ 3, 1, 2 }), "%d");
}
