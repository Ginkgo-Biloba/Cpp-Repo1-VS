#include "leetcode.hpp"

/* 46. 全排列

给定一个 没有重复 数字的序列，返回其所有可能的全排列。

示例:
输入: [1,2,3]
输出:
[
	[1,2,3],
	[1,3,2],
	[2,1,3],
	[2,3,1],
	[3,1,2],
	[3,2,1]
]


47. 全排列 II

给定一个可包含重复数字的序列，返回所有不重复的全排列。

示例:
输入: [1,1,2]
输出:
[
	[1,1,2],
	[1,2,1],
	[2,1,1]
]
*/

// 031
bool nextPermutation(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	bool large = false;
	if (len < 2)
		return large;
	int p = len - 2, q, t;
	for (; p >= 0; --p)
	{
		if (A[p] < A[p + 1])
			break;
	}
	if (p >= 0)
	{
		large = true;
		for (q = len - 1; p < q; --q)
		{
			if (A[p] < A[q])
				break;
		}
		t = A[p];
		A[p] = A[q];
		A[q] = t;
	}
	++p;
	q = len - 1;
	for (; p < q; ++p, --q)
	{
		t = A[p];
		A[p] = A[q];
		A[q] = t;
	}
	return large;
}

vector<vector<int>> permute(vector<int>& A)
{
	vector<vector<int>> R;
	int num = static_cast<int>(A.size());
	for (int i = num - 1; i > 0; --i)
		num *= i;
	R.reserve(num);
	sort(A.begin(), A.end());
	R.push_back(A);
	while (nextPermutation(A))
		R.push_back(A);
	return R;
}


int main()
{
	vector<int> a = { 1, 2, 3 };
	output(permute(a));
}
