#include "leetcode.hpp"

/* 1712. 将数组分成三个子数组的方案数

我们称一个分割整数数组的方案是 好的 ，当它满足：
	数组被分成三个 非空 连续子数组，从左至右分别命名为 left ， mid ， right 。
	left 中元素和小于等于 mid 中元素和，mid 中元素和小于等于 right 中元素和。

给你一个 非负 整数数组 nums ，请你返回 好的 分割 nums 方案数目。
由于答案可能会很大，请你将结果对 10^9 + 7 取余后返回。

示例 1：
输入：nums = [1,1,1]
输出：1
解释：唯一一种好的分割方案是将 nums 分成 [1] [1] [1] 。

示例 2：
输入：nums = [1,2,2,2,5,0]
输出：3
解释：nums 总共有 3 种好的分割方案：
[1] [2] [2,2,5,0]
[1] [2,2] [2,5,0]
[1,2] [2,2] [5,0]

示例 3：
输入：nums = [3,2,1]
输出：0
解释：没有好的分割方案。

提示：
	3 <= nums.length <= 10^5
	0 <= nums[i] <= 10^4
*/

// https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/discuss/999257/C%2B%2BJavaPython-O(n)-with-picture
// 抄的
int waysToSplit(vector<int>& A)
{
	int64_t mod = static_cast<int64_t>(1e9 + 7);
	int64_t ans = 0;
	int len = static_cast<int>(A.size());
	int n1 = len - 1;
	for (int i = 1; i < len; ++i)
		A[i] += A[i - 1];
	for (int i = 0, j = 0, k = 0; i < len - 2; ++i)
	{
		while (j <= i || (j < n1 && A[j] < A[i] * 2))
			++j;
		while (k < j || (k < n1 && A[k] - A[i] <= A[n1] - A[k]))
			++k;
		ans += k - j;
	}
	return static_cast<int>(ans % mod);
}


int main()
{
	vector<int>
		a = { 1, 1, 1 },
		b = { 1, 2, 2, 2, 5, 0 },
		c = { 3, 2, 1 },
		d = { 0, 3, 3 };
	OutExpr(waysToSplit(a), "%d");
	OutExpr(waysToSplit(b), "%d");
	OutExpr(waysToSplit(c), "%d");
	OutExpr(waysToSplit(d), "%d");
}
