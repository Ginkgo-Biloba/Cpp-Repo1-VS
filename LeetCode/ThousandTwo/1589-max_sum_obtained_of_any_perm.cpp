#include "leetcode.hpp"

/* 1589. 所有排列中的最大和

有一个整数数组 nums ，和一个查询数组 requests ，其中 requests[i] = [starti, endi] 。
第 i 个查询求 nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi] 的结果 ，starti 和 endi 数组索引都是 从 0 开始 的。

你可以任意排列 nums 中的数字，请你返回所有查询结果之和的最大值。

由于答案可能会很大，请你将它对 10^9 + 7 取余 后返回。

示例 1：
输入：nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
输出：19
解释：一个可行的 nums 排列为 [2,1,3,4,5]，并有如下结果：
requests[0] -> nums[1] + nums[2] + nums[3] = 1 + 3 + 4 = 8
requests[1] -> nums[0] + nums[1] = 2 + 1 = 3
总和为：8 + 3 = 11。
一个总和更大的排列为 [3,5,4,2,1]，并有如下结果：
requests[0] -> nums[1] + nums[2] + nums[3] = 5 + 4 + 2 = 11
requests[1] -> nums[0] + nums[1] = 3 + 5  = 8
总和为： 11 + 8 = 19，这个方案是所有排列中查询之和最大的结果。

示例 2：
输入：nums = [1,2,3,4,5,6], requests = [[0,1]]
输出：11
解释：一个总和最大的排列为 [6,5,4,3,2,1] ，查询和为 [11]。

示例 3：
输入：nums = [1,2,3,4,5,10], requests = [[0,2],[1,3],[1,1]]
输出：47
解释：一个和最大的排列为 [4,10,5,3,2,1] ，查询结果分别为 [19,18,10]。

提示：
	n == nums.length
	1 <= n <= 10^5
	0 <= nums[i] <= 10^5
	1 <= requests.length <= 10^5
	requests[i].length == 2
	0 <= starti <= endi < n
*/

int maxSumRangeQuery(vector<int>& A, vector<vector<int>>& req)
{
	int numreq = static_cast<int>(req.size());
	int len = static_cast<int>(A.size());
	vector<int> R(len + 1);
	for (int i = 0; i < numreq; ++i)
	{
		R[req[i][0]] += 1;
		R[req[i][1] + 1] -= 1;
	}
	for (int i = 0; i < len; ++i)
		R[i + 1] += R[i];
	R.pop_back();

	// 把最大的数字安排到被查询次数最多的地方
	int64_t sum = 0;
	int64_t const mod = 1e9 + 7;
	sort(R.begin(), R.end());
	sort(A.begin(), A.end());
	for (int i = 0; i < len; ++i)
	{
		sum += static_cast<int64_t>(A[i]) * R[i];
		sum %= mod;
	}
	return static_cast<int>(sum);
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 4, 5 },
		b = { 1, 2, 3, 4, 5, 6 },
		c = { 1, 2, 3, 4, 5, 10 };
	vector<vector<int>>
		o = { { 1, 3 }, { 0, 1 } },
		p = { { 0, 1 } },
		q = { { 0, 2 }, { 1, 3 }, { 1, 1 } };
	OutExpr(maxSumRangeQuery(a, o), "%d");
	OutExpr(maxSumRangeQuery(b, p), "%d");
	OutExpr(maxSumRangeQuery(c, q), "%d");
}
