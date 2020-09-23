#include "leetcode.hpp"

/* 1053. 交换一次的先前排列

给你一个正整数的数组 A（其中的元素不一定完全不同），请你返回可在 一次交换（交换两数字 A[i] 和 A[j] 的位置）后得到的、按字典序排列小于 A 的最大可能排列。

如果无法这么操作，就请返回原数组。

示例 1：
输入：[3,2,1]
输出：[3,1,2]
解释：
交换 2 和 1

示例 2：
输入：[1,1,5]
输出：[1,1,5]
解释：
这已经是最小排列

示例 3：
输入：[1,9,4,6,7]
输出：[1,7,4,6,9]
解释：
交换 9 和 7

示例 4：
输入：[3,1,1,3]
输出：[1,3,1,3]
解释：
交换 1 和 3

提示：
	1 <= A.length <= 10000
	1 <= A[i] <= 10000
*/


vector<int> prevPermOpt1(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int i = len - 1;
	for (; i > 0; --i)
	{
		if (A[i - 1] > A[i])
			break;
	}
	if (i == 0)
		return A;
	int k = i, m = i;
	for (; m < len; ++m)
	{
		if (A[m] < A[i - 1] && A[m] > A[k])
			k = m;
	}
	std::swap(A[i - 1], A[k]);
	return A;
}


int main()
{
	vector<int>
		a = { 3, 2, 1 },
		b = { 1, 1, 5 },
		c = { 1, 9, 4, 6, 7 },
		d = { 3, 1, 1, 3 };
	output(prevPermOpt1(a), "prevPermOpt1");
	output(prevPermOpt1(b), "prevPermOpt1");
	output(prevPermOpt1(c), "prevPermOpt1");
	output(prevPermOpt1(d), "prevPermOpt1");
}
