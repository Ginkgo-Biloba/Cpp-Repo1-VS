#include "leetcode.hpp"

/* 961. 重复 N 次的元素

在大小为 2N 的数组 A 中有 N+1 个不同的元素，其中有一个元素重复了 N 次。

返回重复了 N 次的那个元素。

示例 1：
输入：[1,2,3,3]
输出：3

示例 2：
输入：[2,1,2,5,3,2]
输出：2

示例 3：
输入：[5,1,5,2,5,3,5,4]
输出：5

提示：
	4 <= A.length <= 10000
	0 <= A[i] < 10000
	A.length 为偶数
*/

// https://leetcode.com/problems/n-repeated-element-in-size-2n-array/discuss/208563/JavaC%2B%2BPython-O(1)-Solution
// 抄的
int repeatedNTimes(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	for (int i = 2; i < len; ++i)
	{
		if (A[i - 2] == A[i] || A[i - 1] == A[i])
			return A[i];
	}
	return A[0];
}


int main()
{
	vector<int>
		a = { 1, 2, 3, 3 },
		b = { 2, 1, 2, 5, 3, 2 },
		c = { 5, 1, 5, 2, 5, 3, 5, 4 };
	OutExpr(repeatedNTimes(a), "%d");
	OutExpr(repeatedNTimes(b), "%d");
	OutExpr(repeatedNTimes(c), "%d");
}
