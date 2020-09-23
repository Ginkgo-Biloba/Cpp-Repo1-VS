#include "leetcode.hpp"

/* 152. 乘积最大子数组

给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

示例 1:
输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。

示例 2:
输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
*/

// https://leetcode.com/problems/maximum-product-subarray/discuss/48230/Possibly-simplest-solution-with-O(n)-time-complexity
// 抄的
int maxProduct(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int ans = A[0], pos = A[0], neg = A[0];
	for (int i = 1; i < len; ++i)
	{
		if (A[i] < 0)
			std::swap(pos, neg);
		pos = max(A[i], pos * A[i]);
		neg = min(A[i], neg * A[i]);
		ans = max(ans, pos);
	}
	return ans;
}

int main()
{
	vector<int>
		a = { 2, 3, -2, 4 },
		b = { -2, 0, -1 };
	OutExpr(maxProduct(a), "%d");
	OutExpr(maxProduct(b), "%d");
}
