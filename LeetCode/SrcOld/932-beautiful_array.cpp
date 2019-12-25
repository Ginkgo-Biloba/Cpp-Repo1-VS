#include "leetcode.hpp"

/* 932. 漂亮数组

对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，使得：

对于每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]。

那么数组 A 是漂亮数组。

给定 N，返回任意漂亮数组 A（保证存在一个）。

示例 1：
输入：4
输出：[2,1,4,3]

示例 2：
输入：5
输出：[3,1,2,5,4]

提示：
	1 <= N <= 1000
*/

// https://leetcode.com/problems/beautiful-array/discuss/186679/Odd-%2B-Even-Pattern-O(N)
// 抄的
vector<int> beautifulArray(int N)
{
	size_t szN = N;
	vector<int> A, B;
	A.reserve(szN);
	B.reserve(szN);
	A.push_back(1);
	while (A.size() < szN)
	{
		B.clear();
		for (int a : A)
		{
			int b = 2 * a - 1;
			if (b <= N)
				B.push_back(b);
		}
		for (int a : A)
		{
			int b = 2 * a;
			if (b <= N)
				B.push_back(b);
		}
		B.swap(A);
	}
	return A;
}

int main()
{
	output(beautifulArray(4), "Beautiful Array");
	output(beautifulArray(5), "Beautiful Array");
}
