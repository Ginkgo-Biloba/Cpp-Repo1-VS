#include "leetcode.hpp"

/* 1124. 表现良好的最长时间段

给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。

我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。

所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。

请你返回「表现良好时间段」的最大长度。

示例 1：
输入：hours = [9,9,6,0,6,6,9]
输出：3
解释：最长的表现良好时间段是 [9,9,6]。

提示：
	1 <= hours.length <= 10000
	0 <= hours[i] <= 16
*/

// https://leetcode.com/problems/longest-well-performing-interval/discuss/335163/O(N)-Without-Hashmap.-Generalized-ProblemandSolution%3A-Find-Longest-Subarray-With-Sum-greater-K.
// 参考 962
class Solution
{
public:
	int longestWPI(vector<int>& hours)
	{
		int len = static_cast<int>(hours.size());
		vector<int> acc(len + 1), dec;
		for (int i = 0; i < len; ++i)
			acc[i + 1] = acc[i] + (hours[i] > 8 ? 1 : -1);

		dec.swap(hours);
		dec.clear();
		for (int i = 0; i <= len; ++i)
		{
			if (dec.empty()
				|| acc[dec.back()] > acc[i])
				dec.push_back(i);
		}

		int ans = 0;
		for (int i = len; i >= 0; --i)
			while (!dec.empty()
				&& acc[dec.back()] < acc[i])
			{
				ans = max(ans, i - dec.back());
				dec.pop_back();
			}
		return ans;
	}
};


int main()
{
	Solution s;
	vector<int> a = { 9, 9, 6, 0, 6, 6, 9, 9, 9, 9, 9 };
	OutExpr(s.longestWPI(a), "%d");
}
