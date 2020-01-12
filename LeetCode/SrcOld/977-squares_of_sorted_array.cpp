#include "leetcode.hpp"

/* 977. 有序数组的平方

给定一个按非递减顺序排序的整数数组 A，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。

示例 1：
输入：[-4,-1,0,3,10]
输出：[0,1,9,16,100]

示例 2：
输入：[-7,-3,2,3,11]
输出：[4,9,9,49,121]

提示：
	1 <= A.length <= 10000
	-10000 <= A[i] <= 10000
	A 已按非递减顺序排序。
*/

vector<int> sortedSquares(vector<int>& A)
{
	int n = static_cast<int>(A.size());
	vector<int> B;
	B.reserve(n);

	for (int k = 0; k < n; ++k)
		A[k] *= A[k];
	for (int i = 0, k = n - 1; i <= k;)
	{
		if (A[i] > A[k])
		{
			B.push_back(A[i]);
			++i;
		}
		else
		{
			B.push_back(A[k]);
			--k;
		}
	}

	reverse(B.begin(), B.end());
	return B;
}

int main()
{
	vector<int>
		a = { -4, -1, 0, 3, 10 },
		b = { -7, -3, 2, 3, 11 };
	output(sortedSquares(a), "Squares of a Sorted Array");
	output(sortedSquares(b), "Squares of a Sorted Array");
}
