#include "leetcode.hpp"

/* 775. 全局倒置与局部倒置

数组 A 是 [0, 1, ..., N - 1] 的一种排列，N 是数组 A 的长度。
全局倒置指的是 i,j 满足 0 <= i < j < N 并且 A[i] > A[j]。
局部倒置指的是 i 满足 0 <= i < N 并且 A[i] > A[i+1] 。

当数组 A 中全局倒置的数量等于局部倒置的数量时，返回 true 。

示例 1:
输入: A = [1,0,2]
输出: true
解释: 有 1 个全局倒置，和 1 个局部倒置。

示例 2:
输入: A = [1,2,0]
输出: false
解释: 有 2 个全局倒置，和 1 个局部倒置。

注意:
	A 是 [0, 1, ..., A.length - 1] 的一种排列
	A 的长度在 [1, 5000]之间
	这个问题的时间限制已经减少了。
*/

// https://leetcode.com/problems/global-and-local-inversions/discuss/113656/My-3-lines-C%2B%2B-Solution
// 抄的
bool isIdealPermutation(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	for (int i = 0; i < len; ++i)
	{
		if (abs(A[i] - i) > 1)
			return false;
	}
	return true;
}


int main()
{
	vector<int>
		n0 = { 1, 0, 2 },
		n1 = { 1, 2, 0 };
	OutBool(isIdealPermutation(n0));
	OutBool(isIdealPermutation(n1));
}
