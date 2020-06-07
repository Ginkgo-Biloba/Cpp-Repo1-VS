#include "leetcode.hpp"

/* 349. 两个数组的交集

给定两个数组，编写一个函数来计算它们的交集。

示例 1:

输入: nums1 = [1,2,2,1], nums2 = [2,2]
输出: [2]

示例 2:

输入: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出: [9,4]

说明:
	输出结果中的每个元素一定是唯一的。
	我们可以不考虑输出结果的顺序。
*/

vector<int> intersection(vector<int>& A, vector<int>& B)
{
	int a = static_cast<int>(A.size());
	int b = static_cast<int>(B.size());
	vector<int> C;
	int h = 0, i = 0;
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	while (h < a && i < b)
	{
		if (A[h] < B[i])
		{
			while (h < a && A[h] < B[i])
				++h;
		}
		else if (A[h] > B[i])
		{
			while (i < b && A[h] > B[i])
				++i;
		}
		else // (A[h] == B[i])
		{
			C.push_back(A[h]);
			while (h < a && A[h] == C.back())
				++h;
			while (i < b && B[i] == C.back())
				++i;
		}
	}
	return C;
}


int main()
{
	vector<int>
		a = { 1, 2, 2, 1 },
		b = { 2, 2 },
		c = { 4, 9, 5 },
		d = { 9, 4, 9, 8, 4 };
	output(intersection(a, b));
	output(intersection(c, d));
}
